package cs201game.threads;

import cs201game.ServerMain;
import cs201game.models.*;
import cs201game.protos.*;
import cs201game.util.ControllerLogger;
import cs201game.util.Database;

import java.io.IOException;
import java.net.Socket;

public class Controller extends Thread {
    private final ServerMain server;
    private final ControllerLogger logger = new ControllerLogger(this);
    private final Socket socket;
    private Listener listener;
    private Sender sender;
    private int tempId;
    private int playerId;

    public Controller(Socket socket, ServerMain server, int tempId) {
        this.server = server;
        this.socket = socket;
        try {
            this.listener = new Listener(socket.getInputStream(), logger);
            this.sender = new Sender(socket.getOutputStream(), logger);
            this.tempId = tempId;
            this.playerId = -1;
        } catch (IOException ie) {
            ie.printStackTrace();
        }

    }

    @Override
    public void run() {
        listener.start();
        sender.start();
        while (true) {
            Object message = null;
            try {
                message = listener.getInMsgQueue().take();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            assert message != null;
            if (message instanceof LoginRequest) {
                AuthProto.AuthRequest authRequest = ((LoginRequest) message).getAuthRequest();
                if (Database.checkCredentials(authRequest.getUsername(), authRequest.getPassword())) {
                    System.out.println("Info verification success");
                    playerId = Database.getUserID(authRequest.getUsername());
                    if (server.attemptLogin(playerId)) {
                        queueMessageForSend(LoginResponseProto.LoginResponse.newBuilder().setSuccess(0).build());
                    } else {
                        // 2 for duplicate login
                        queueMessageForSend(LoginResponseProto.LoginResponse.newBuilder().setSuccess(2).build());
                    }
                    //login success
                    /*1: Login Response
                    StatusCode: Int
                    0: Success
                    1: Username or password is not correct.
                    */
                } else {
                    logger.log("Invalid credentials.");
                    // 1 for invalid credentials
                    queueMessageForSend(LoginResponseProto.LoginResponse.newBuilder().setSuccess(1).build());
                    forceDropConnection();
                    break;
                }
            } else if (message instanceof RegisterRequest) {
                logger.log("Creating user.");
                AuthProto.AuthRequest authRequest = ((RegisterRequest) message).getAuthRequest();
                int result = Database.addUser(authRequest.getUsername(), authRequest.getPassword());
                RegisterResponseProto.RegisterResponse response =
                        RegisterResponseProto.RegisterResponse.newBuilder().setStatusCode(result).build();
                queueMessageForSend(response);
                if (response.getStatusCode() == 0) {
                    logger.log("User creation success.");
                    playerId = Database.getUserID(authRequest.getUsername());//get from database;
                }
            } else if (message instanceof PlayerInfoProto.PlayerInfo) {
                PlayerInfoProto.PlayerInfo.Builder infoToSend = PlayerInfoProto.PlayerInfo.newBuilder();
                infoToSend.setId(playerId);
                infoToSend.setX(((PlayerInfoProto.PlayerInfo) message).getX());
                infoToSend.setY(((PlayerInfoProto.PlayerInfo) message).getY());
                infoToSend.setRotation(((PlayerInfoProto.PlayerInfo) message).getRotation());
                server.broadcastMessageToAllClients(infoToSend.build(), this);
            } else if (message instanceof PlayerFinishProto.PlayerFinish) {
                Database.updateLeaderboard(playerId, ((PlayerFinishProto.PlayerFinish) message).getScore());
                server.broadcastMessageToAllClients(new PlayerRemoved(playerId), this);
            } else if (message instanceof PlayerDied) {
                ((PlayerDied) message).playerID = playerId;
                server.broadcastMessageToAllClients(message, this);
            } else if (message instanceof LeaderboardRequest) {
                LeaderboardProto.Leaderboard leaderboard = Database.queryLeaderboard();
                queueMessageForSend(leaderboard);
            } else if (message instanceof PlayerDisconnected) {
                ((PlayerDisconnected) message).playerID = playerId;
                forceDropConnection();
                server.broadcastMessageToAllClients(message, this);
                break;
            } else {
                logger.log(String.format("[Controller Thread] %s", message.getClass().toString()));
            }
        }
    }


    public void queueMessageForSend(Object message) {
        sender.getOutMsgQueue().add(message);
    }

    public int getTempId() {
        return tempId;
    }

    public int getPlayerId() {
        return playerId;
    }

    public void forceDropConnection() {
        try {
            if (socket != null) {
                sender.getOutMsgQueue().add(new NoMoreMessage());
                sender.join();
                socket.close();
                listener.join();
                server.dropConnection(this);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}

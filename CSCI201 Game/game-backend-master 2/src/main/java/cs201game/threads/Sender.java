package cs201game.threads;

import cs201game.models.NoMoreMessage;
import cs201game.models.PlayerDied;
import cs201game.models.PlayerDisconnected;
import cs201game.models.PlayerRemoved;
import cs201game.protos.*;
import cs201game.util.ControllerLogger;
import cs201game.util.PrettyPrinter;

import java.io.IOException;
import java.io.OutputStream;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class Sender extends Thread {
    public static final int MSG_ID_LOGIN_RESPONSE = 1;
    public static final int MSG_ID_REGISTER_RESPONSE = 2;
    public static final int MSG_ID_GAME_INFO = 3;
    public static final int MSG_ID_PLAYER_DISCONNECTED = 4;
    public static final int MSG_ID_PLAYER_REMOVED = 5;
    public static final int MSG_ID_PLAYER_DIED = 6;
    public static final int MSG_ID_LEADERBOARD = 7;


    private final OutputStream stream;
    private final LinkedBlockingQueue<Object> outMsgQueue;
    private final ControllerLogger logger;

    public Sender(OutputStream outputStream, ControllerLogger logger) {
        this.stream = outputStream;
        this.logger = logger;
        this.outMsgQueue = new LinkedBlockingQueue<>();
    }

    public BlockingQueue<Object> getOutMsgQueue() {
        return outMsgQueue;
    }

    @Override
    public void run() {
        try {
            //noinspection InfiniteLoopStatement
            while (true) {
                Object outputObject = takeMessageFromQueue();
                if (outputObject instanceof LoginResponseProto.LoginResponse) {
                    MessageTypeProto.MessageType.newBuilder().setType(MSG_ID_LOGIN_RESPONSE).build().writeDelimitedTo(stream);
                    ((LoginResponseProto.LoginResponse) outputObject).writeDelimitedTo(stream);
                } else if (outputObject instanceof RegisterResponseProto.RegisterResponse) {
                    MessageTypeProto.MessageType.newBuilder().setType(MSG_ID_REGISTER_RESPONSE).build().writeDelimitedTo(stream);
                    ((RegisterResponseProto.RegisterResponse) outputObject).writeDelimitedTo(stream);
                } else if (outputObject instanceof PlayerInfoProto.PlayerInfo) {
                    MessageTypeProto.MessageType.newBuilder().setType(MSG_ID_GAME_INFO).build().writeDelimitedTo(stream);
                    ((PlayerInfoProto.PlayerInfo) outputObject).writeDelimitedTo(stream);
                } else if (outputObject instanceof PlayerRemoved) {
                    MessageTypeProto.MessageType.newBuilder().setType(MSG_ID_PLAYER_REMOVED).build().writeDelimitedTo(stream);
                    PlayerIDProto.PlayerID.newBuilder().setID(((PlayerRemoved) outputObject).playerID).build()
                            .writeDelimitedTo(stream);
                } else if (outputObject instanceof PlayerDied) {
                    MessageTypeProto.MessageType.newBuilder().setType(MSG_ID_PLAYER_DIED).build().writeDelimitedTo(stream);
                    PlayerIDProto.PlayerID.newBuilder().setID(((PlayerDied) outputObject).playerID).build()
                            .writeDelimitedTo(stream);
                } else if (outputObject instanceof LeaderboardProto.Leaderboard) {
                    MessageTypeProto.MessageType.newBuilder().setType(MSG_ID_LEADERBOARD).build().writeDelimitedTo(stream);
                    ((LeaderboardProto.Leaderboard) outputObject).writeDelimitedTo(stream);
                } else if (outputObject instanceof PlayerDisconnected) {
                    MessageTypeProto.MessageType.newBuilder().setType(MSG_ID_PLAYER_DISCONNECTED).build().writeDelimitedTo(stream);
                    PlayerIDProto.PlayerID.newBuilder().setID(((PlayerDisconnected) outputObject).playerID).build()
                            .writeDelimitedTo(stream);
                } else if (outputObject instanceof NoMoreMessage) {
                    break;
                }
            }
        } catch (InterruptedException | IOException e) {
            e.printStackTrace();
        }
    }

    private Object takeMessageFromQueue() throws InterruptedException {
        Object message = outMsgQueue.take();
        logger.log(String.format("Send message: %s", PrettyPrinter.prettyPrint(message)));
        return message;
    }
}

package cs201game;

import cs201game.models.LoginRequest;
import cs201game.protos.AuthProto;
import cs201game.protos.LoginResponseProto;
import cs201game.threads.Controller;
import cs201game.util.Database;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

public class ServerMain {
    private final List<Controller> controllers = Collections.synchronizedList(new ArrayList<>());
    private final Set<Integer> loggedInUsers = Collections.synchronizedSet(new HashSet<>());

    public ServerMain() {
        try {
            ServerSocket ss = new ServerSocket(3456);
            Database.connectToDatabase("localhost");
            int temp_id = 0;
            //noinspection InfiniteLoopStatement
            while (true) {
                Socket s = ss.accept();
                System.out.println("New player connected! :D");
                Controller controller = new Controller(s, this, temp_id);
                controller.start();
                controllers.add(controller);
                temp_id++;
            }
        } catch (IOException ie) {
            ie.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new ServerMain();
    }

    public void dropConnection(Controller toBeDropped) {
        controllers.remove(toBeDropped);
        loggedInUsers.remove(toBeDropped.getPlayerId());
    }

    public void broadcastMessageToAllClients(Object message, Controller sender) {
        synchronized (controllers) {
            for (Controller controller : controllers) {
                if (controller != sender) {
                    controller.queueMessageForSend(message);
                }
            }
        }
    }

    public boolean attemptLogin(int playerID) {
        if (loggedInUsers.contains(playerID)) {
            return false;
        } else {
            loggedInUsers.add(playerID);
            return true;
        }
    }
}

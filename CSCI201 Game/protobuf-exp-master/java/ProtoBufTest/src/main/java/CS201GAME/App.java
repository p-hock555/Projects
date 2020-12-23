package CS201GAME;

import CS201GAME.protos.AuthCredentialProto.AuthCredential;
import CS201GAME.protos.PlayerChangeProto.PlayerChange;
import CS201GAME.protos.PlayerStatusProto.PlayerStatus;
import com.google.protobuf.CodedInputStream;
import com.google.protobuf.CodedOutputStream;

import java.io.FileOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class App {
    public static void main(String[] args) {
        AuthCredential auth = AuthCredential.newBuilder().setUsername("a").setPassword("b").build();
        PlayerChange change = PlayerChange.newBuilder().setName("aaron").setEnterExit(false).build();
        PlayerStatus status = PlayerStatus.newBuilder().setName("aaron").setRotation(0).setX(1).setY(2).setZ(3).build();
        try {
            ServerSocket ss = new ServerSocket(3456);
            Socket s = ss.accept();
            System.out.println("New connection from " + s.getInetAddress());
            auth.writeDelimitedTo(s.getOutputStream());
            change.writeDelimitedTo(s.getOutputStream());
            status = PlayerStatus.parseDelimitedFrom(s.getInputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (status == null) {
            System.out.println("null");
        } else {
            System.out.println(status.getName());
            System.out.println(status.getX());
            System.out.println(status.getY());
            System.out.println(status.getZ());
            System.out.println(status.getRotation());
        }
    }
}

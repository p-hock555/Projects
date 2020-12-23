package cs201game.util;

import cs201game.models.LoginRequest;
import cs201game.models.PlayerDisconnected;
import cs201game.models.PlayerRemoved;
import cs201game.models.RegisterRequest;
import cs201game.protos.LoginResponseProto;
import cs201game.protos.PlayerInfoProto;
import cs201game.protos.RegisterResponseProto;

public class PrettyPrinter {
    public static String prettyPrint(Object message) {
        if (message instanceof LoginRequest) {
            LoginRequest loginRequest = (LoginRequest) message;
            return String.format("LoginRequest: { username = '%s', password = '%s' }",
                    loginRequest.getAuthRequest().getUsername(),
                    loginRequest.getAuthRequest().getPassword());
        } else if (message instanceof RegisterRequest) {
            return String.format("RegisterRequest: { username = '%s', password = '%s' }",
                    ((RegisterRequest) message).getAuthRequest().getUsername(),
                    ((RegisterRequest) message).getAuthRequest().getPassword());
        } else if (message instanceof RegisterResponseProto.RegisterResponse) {
            return String.format("RegisterResponse: { status = %s }",
                    ((RegisterResponseProto.RegisterResponse) message).getStatusCode());
        } else if (message instanceof LoginResponseProto.LoginResponse) {
            return String.format("LoginResponse: { success = %s }",
                    ((LoginResponseProto.LoginResponse) message).getSuccess());
        } else if (message instanceof PlayerInfoProto.PlayerInfo) {
            return String.format("PlayerInfo: { x = %s, y = %s }",
                    ((PlayerInfoProto.PlayerInfo) message).getX(),
                    ((PlayerInfoProto.PlayerInfo) message).getY());
        } else if (message instanceof PlayerDisconnected) {
            return String.format("PlayerDisconnected: { playerID = %s }", ((PlayerDisconnected) message).playerID);
        } else if (message instanceof PlayerRemoved) {
            return String.format("PlayerRemove: { playerID = %s }", ((PlayerRemoved) message).playerID);
        } else {
            return String.format("Unknown message type: %s", message.getClass().toString());
        }
    }
}

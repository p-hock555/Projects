package cs201game.models;

import cs201game.protos.AuthProto;

public class LoginRequest {
    private final AuthProto.AuthRequest authRequest;

    public LoginRequest(AuthProto.AuthRequest authRequest) {
        this.authRequest = authRequest;
    }

    public AuthProto.AuthRequest getAuthRequest() {
        return authRequest;
    }
}

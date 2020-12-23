package cs201game.models;

import cs201game.protos.AuthProto;

public class RegisterRequest {
    private final AuthProto.AuthRequest authRequest;

    public RegisterRequest(AuthProto.AuthRequest authRequest) {
        this.authRequest = authRequest;
    }

    public AuthProto.AuthRequest getAuthRequest() {
        return authRequest;
    }
}

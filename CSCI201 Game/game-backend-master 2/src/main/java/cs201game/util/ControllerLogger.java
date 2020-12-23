package cs201game.util;

import cs201game.threads.Controller;

public class ControllerLogger {
    private final Controller controller;

    public ControllerLogger(Controller controller) {
        this.controller = controller;
    }

    public void log(String message) {
        String controllerId = controller.getPlayerId() == -1 ?
                Integer.toString(controller.getTempId()) :
                String.format("authed %d", controller.getPlayerId());
        System.out.println(String.format("[Controller %s] %s", controllerId, message));
    }
}

package cs201game.threads;

import cs201game.models.*;
import cs201game.protos.*;
import cs201game.util.ControllerLogger;
import cs201game.util.PrettyPrinter;

import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class Listener extends Thread {

    public static final int MSG_ID_LOGIN_REQUEST = 1;
    public static final int MSG_ID_REGISTER_REQUEST = 2;
    public static final int MSG_ID_PLAYER_INFO = 3;
    public static final int MSG_ID_PLAYER_FINISH = 4;
    public static final int MSG_ID_PLAYER_DIED = 5;
    public static final int MSG_ID_LEADERBOARD = 7;

    private final InputStream stream;//reading messages/to be deserialized
    private final LinkedBlockingQueue<Object> inMsgQueue;
    private final ControllerLogger logger;

    public Listener(InputStream inputStream, ControllerLogger logger) {
        this.stream = inputStream;
        this.logger = logger;
        this.inMsgQueue = new LinkedBlockingQueue<>();
    }

    public BlockingQueue<Object> getInMsgQueue() {
        return inMsgQueue;
    }

    @Override
    public void run() {
        try {
            while (true) {
                int messageId = MessageTypeProto.MessageType.parseDelimitedFrom(stream).getType();
                // todo: use different message type for login and register
                if (messageId == MSG_ID_LOGIN_REQUEST) {
                    Object message = new LoginRequest(AuthProto.AuthRequest.parseDelimitedFrom(stream));
                    queueMessage(message);
                } else if (messageId == MSG_ID_REGISTER_REQUEST) {
                    Object message = new RegisterRequest(AuthProto.AuthRequest.parseDelimitedFrom(stream));
                    queueMessage(message);
                } else if (messageId == MSG_ID_PLAYER_INFO) {
                    Object message = PlayerInfoProto.PlayerInfo.parseDelimitedFrom(stream);
                    queueMessage(message);
                } else if (messageId == MSG_ID_PLAYER_FINISH) {
                    Object message = PlayerFinishProto.PlayerFinish.parseDelimitedFrom(stream);
                    queueMessage(message);
                } else if (messageId == MSG_ID_PLAYER_DIED) {
                    queueMessage(new PlayerDied());
                } else if (messageId == MSG_ID_LEADERBOARD) {
                    queueMessage(new LeaderboardRequest());
                } else {
                    throw new IOException("Unknown message id!");
                }
            }
        } catch (IOException | NullPointerException e) {
            // Connection dropped
            inMsgQueue.add(new PlayerDisconnected());
        }
    }

    private void queueMessage(Object message) {
        assert message != null;
        logger.log(PrettyPrinter.prettyPrint(message));
        inMsgQueue.add(message);
    }
}

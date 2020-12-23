package cs201game.util;

import org.mindrot.jbcrypt.BCrypt;

public class CryptUtil {
    public static String hashAndSaltPassword(String password) {
        return BCrypt.hashpw(password, BCrypt.gensalt());
    }

    public static boolean checkPassword(String password, String hash) {
        return BCrypt.checkpw(password, hash);
    }
}

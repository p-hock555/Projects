package cs201game.util;

import cs201game.protos.LeaderboardProto;
import cs201game.protos.PlayerScoreProto;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.sql.*;
import java.util.regex.Pattern;

public class Database {

    private static Connection conn;

    public static void connectToDatabase(String address) {
        FileReader fr = null;
        BufferedReader br = null;
        try {
            fr = new FileReader("db.cred");
            br = new BufferedReader(fr);
            String password = br.readLine();
            conn = DriverManager.getConnection("jdbc:mysql://" + address + "/GameData?user=root&password=" + password);
        } catch (IOException | SQLException exception) {
            exception.printStackTrace();
        } finally {
            if (fr != null) {
                try {
                    fr.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if (br != null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /*
     * 0: Success
     * Error Bit Flags: {
     *     1: Username has already been taken;
     *     2: Username contains illegal characters;
     *     4: Username is too long or too short;
     *     8: Password is too long or too short;
     * }
     */
    public static int addUser(String username, String password) {
        PreparedStatement stmt = null;
        ResultSet rs;
        // Check username length
        int errorFlags = 0;

        if (username.length() < 4 || username.length() > 16) {
            errorFlags |= 4;
        }
        // Check for illegal characters
        if (!Pattern.matches("^[A-Za-z0-9_-]*$", username)) {
            errorFlags |= 2;
        }
        // Check password length
        if (password.length() < 8 || password.length() > 20) {
            errorFlags |= 8;
        }

        if (errorFlags != 0) {
            return errorFlags;
        }

        try {
            // Check for username duplicate
            assert conn != null;
            stmt = conn.prepareStatement("SELECT EXISTS(SELECT playerID FROM Players WHERE username=?)");
            stmt.setString(1, username);
            rs = stmt.executeQuery();
            System.out.println("Querying for existing user.");
            if (rs.next() && rs.getInt(1) == 1) {
                System.out.println("User exists.");
                return 1;
            }
            stmt.close();
            System.out.println("Closing stmt");
            stmt = conn.prepareStatement("INSERT INTO Players (username, password) VALUES (?, ?)");
            System.out.println("Preparing statement");
            stmt.setString(1, username);
            System.out.println("setting username");
            stmt.setString(2, CryptUtil.hashAndSaltPassword(password));
            System.out.println("Inserting new user.");
            stmt.executeUpdate();
            return 0;
        } catch (SQLException sqle) {
            sqle.printStackTrace();
        } finally {
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException sqle) {
                    sqle.printStackTrace();
                }
            }
        }
        return -1;
    }

    public static boolean checkCredentials(String username, String password) {

        // todo: remove debug credentials
        if (username.equals("root") && password.equals("root")) {
            return true;
        }

        PreparedStatement stmt = null;
        ResultSet rs;
        try {
            stmt = conn.prepareStatement("SELECT password FROM Players WHERE username=?");
            stmt.setString(1, username);
            rs = stmt.executeQuery();
            if (rs.next()) {
                return CryptUtil.checkPassword(password, rs.getString("password").trim());
            } else {
                return false;
            }
        } catch (SQLException sqle) {
            sqle.printStackTrace();
        } finally {
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException sqle) {
                    sqle.printStackTrace();
                }
            }
        }
        return false;
    }

    synchronized public static void updateLeaderboard(int playerID, double score) {
        PreparedStatement stmt = null;
        try {
            //check if player already exists
            stmt = conn.prepareStatement("CALL UpdateLeaderboard(?, ?)");
            stmt.setInt(1, playerID);
            stmt.setDouble(2, score);
            stmt.executeUpdate();
        } catch (SQLException sqle) {
            sqle.printStackTrace();
        } finally {
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException sqle) {
                    sqle.printStackTrace();
                }
            }
        }
    }

    public static LeaderboardProto.Leaderboard queryLeaderboard() {
        PreparedStatement stmt = null;
        ResultSet rs;
        LeaderboardProto.Leaderboard.Builder builder = LeaderboardProto.Leaderboard.newBuilder();
        try {
            stmt = conn.prepareStatement(
                    "SELECT username, score FROM Leaderboard l, Players p WHERE l.playerID=p.playerID ORDER BY score");
            rs = stmt.executeQuery();
            while (rs.next()) {
                PlayerScoreProto.PlayerScore playerScore = PlayerScoreProto.PlayerScore.newBuilder()
                        .setUsername(rs.getString("username"))
                        .setScore(rs.getDouble("score")).build();
                builder.addScores(playerScore);
            }
            return builder.build();
        } catch (SQLException sqle) {
            sqle.printStackTrace();
            return null;
        } finally {
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException sqle) {
                    sqle.printStackTrace();
                }
            }
        }
    }

    public static int getUserID(String username) {
        PreparedStatement stmt = null;
        ResultSet rs;
        try {
            stmt = conn.prepareStatement("SELECT playerID FROM Players WHERE username=?");
            stmt.setString(1, username);
            rs = stmt.executeQuery();
            rs.next();
            return rs.getInt("playerID");

        } catch (SQLException sqle) {
            sqle.printStackTrace();
        } finally {
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException sqle) {
                    sqle.printStackTrace();
                }
            }
        }
        return -1;
    }

}

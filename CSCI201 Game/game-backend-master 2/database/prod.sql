DROP DATABASE IF EXISTS GameData;
CREATE DATABASE GameData;

USE GameData;

CREATE TABLE Players
(
    playerID INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(20) NOT NULL,
    password BINARY(80)  NOT NULL
);

CREATE TABLE Leaderboard
(
    leaderboardID INT PRIMARY KEY AUTO_INCREMENT,
    playerID      INT    NOT NULL,
    score         DOUBLE NOT NULL,
    FOREIGN KEY (playerID) REFERENCES Players (playerID)
);

DELIMITER //
CREATE PROCEDURE UpdateLeaderboard(IN newPlayerID INT,
                                   IN newScore DOUBLE)
BEGIN
    DECLARE record_exists INT;
    START TRANSACTION;
    SELECT EXISTS(SELECT playerID FROM Leaderboard WHERE playerID = newPlayerID) INTO record_exists;
    IF record_exists = 1 THEN
        UPDATE Leaderboard
        SET score=LEAST(score, newScore)
        WHERE playerID = newPlayerID;
    ELSE
        SELECT GET_LOCK('lock', 10);
        INSERT INTO Leaderboard (playerID, score) VALUE (newPlayerID, newScore);
        DELETE
        FROM Leaderboard
        WHERE playerID NOT IN (SELECT * FROM (SELECT playerID FROM Leaderboard ORDER BY score LIMIT 10) AS t1);
        SELECT RELEASE_LOCK('lock');
    END IF;
    COMMIT;
END//

DELIMITER ;
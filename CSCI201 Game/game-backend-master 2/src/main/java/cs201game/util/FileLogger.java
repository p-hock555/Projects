package cs201game.util;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class FileLogger {

    public FileLogger(String filename) {
        try {
            File file = new File(filename);
            file.delete();
            FileWriter fw = new FileWriter(filename);
            pw = new PrintWriter(fw);
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

    private PrintWriter pw;

    public void log(String str) {
        pw.println(str);
    }
}

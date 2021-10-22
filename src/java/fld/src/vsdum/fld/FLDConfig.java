package vsdum.fld;

import java.util.Random;

public class FLDConfig {
    
    public static final Random rand = new Random();
    public static int minimumDecayTime = 4;
    public static int maximumDecayTime = 11;
    public static int baseDecayTime = minimumDecayTime;
    public static int randomizationTime = maximumDecayTime - minimumDecayTime;

    private static void update()
    {
        baseDecayTime = minimumDecayTime;
        randomizationTime = maximumDecayTime - minimumDecayTime;
    }

    public static void setMinimumDecayTime(int value)
    {
        minimumDecayTime = value;
        update();
    }

    public static void setMaximumDecayTime(int value)
    {
        maximumDecayTime = value;
        update();
    }

    public static int generateDelay()
    {
        return baseDecayTime + rand.nextInt(randomizationTime);
    }

}

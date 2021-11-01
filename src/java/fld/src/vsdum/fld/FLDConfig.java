package vsdum.fld;

import java.util.Random;

public class FLDConfig {
    
    public static final Random rand = new Random();
    public static int decaySpeed;
    public static int decayFuzz;

    public static void setDecaySpeed(int speed)
    {
        decaySpeed = speed;
    }

    public static void setDecayFuzz(int fuzz)
    {
        decayFuzz = fuzz;
    }

}

package vsdum.fld;

import java.util.HashMap;

import static vsdum.fld.FLDConfig.*;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class FastLeafDecay {
    
    private static native void initJNI();
    
    public static void boot(HashMap<?, ?> something)
    {
        initJNI();
        Logger.debug("FastLeafDecay", "Loading java...");
    }
    
    public static void notifyNeighbors(int changedX, int changedY, int changedZ, int x, int y, int z, int dimension)
    {
        NativeBlockSource world = NativeBlockSource.getDefaultForDimension(dimension);
        int notifierId = world.getBlockId(x, y, z);
        if(notifierId == 0)
        {
            if(LeafTickScheduler.isBlockPresent(world.getPointer(), changedX, changedY, changedZ))
            {
                int id = world.getBlockId(changedX, changedY, changedZ);
                if(id == 18 || id == 161)
                {
                    LeafTickScheduler.INSTANCE.schedule(world, changedX, changedY, changedZ, decaySpeed + (decayFuzz > 0 ? rand.nextInt(decayFuzz) : 0));
                }
            }
        }
    }

}

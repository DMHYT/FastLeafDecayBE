package vsdum.fld;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.MCSystem;

public class FastLeafDecay {
    
    private static native void injectJNIEnv();

    private static final int PERSISTENT_BIT = 48;
    private static final int UPDATE_BIT = 54;
    private static final int OLD_LEAF_TYPE = 75;
    private static final int NEW_LEAF_TYPE = 76;
    
    public static void boot(HashMap<?, ?> something)
    {
        injectJNIEnv();
        Logger.debug("FastLeafDecay", "Loading java...");
    }

    public static void onLeafDecayRun(int x, int y, int z, int dimension)
    {
        NativeBlockSource world = NativeBlockSource.getDefaultForDimension(dimension);
        MCSystem.getNetwork().sendServerMessage(String.format("Hooked leaf decay run on %d %d %d", new Object[]{ Integer.valueOf(x), Integer.valueOf(y), Integer.valueOf(z) }));
        schedule(world, new Vec3i(x, y, z), FLDConfig.generateDelay());
    }

    private static final List<ScheduledTick> planned = new ArrayList<ScheduledTick>();
    private static final List<ScheduledTick> scheduled = new ArrayList<ScheduledTick>();

    private static void schedule(NativeBlockSource world, Vec3i pos, int delay)
    {
        planned.add(new ScheduledTick(world, pos, delay));
    }

    public static void tick()
    {
        if(!planned.isEmpty())
        {
            scheduled.addAll(planned);
            planned.clear();
        }
        Iterator<ScheduledTick> iter = scheduled.iterator();
        while(iter.hasNext())
        {
            ScheduledTick st = iter.next();
            if(--st.tick <= 0)
            {
                iter.remove();
                BlockState state = st.world.getBlock(st.pos.x, st.pos.y, st.pos.z);
                if(state.hasState(OLD_LEAF_TYPE) || state.hasState(NEW_LEAF_TYPE))
                {
                    if(state.getState(PERSISTENT_BIT) == 1)
                    {
                        state.addState(PERSISTENT_BIT, 0);
                    }
                    if(state.getState(UPDATE_BIT) == 0)
                    {
                        state.addState(UPDATE_BIT, 1);
                    }
                    st.world.setBlock(st.pos.x, st.pos.y, st.pos.z, state);
                }
            }
        }
    }

    private static class ScheduledTick {
        
        public final NativeBlockSource world;
        public final Vec3i pos;
        public int tick;

        public ScheduledTick(NativeBlockSource world, Vec3i pos, int tick)
        {
            this.world = world;
            this.pos = pos;
            this.tick = tick;
        }

    }

    private static class Vec3i {

        public int x;
        public int y;
        public int z;

        public Vec3i(int x, int y, int z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public boolean equals(Object obj)
        {
            if(obj == this) return true;
            if(obj == null || !(obj instanceof Vec3i)) return false;
            Vec3i vec = (Vec3i) obj;
            return vec.x == this.x && vec.y == this.y && vec.z == this.z;
        }

    }

}

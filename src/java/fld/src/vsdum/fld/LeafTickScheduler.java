package vsdum.fld;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

public class LeafTickScheduler {

    public static native boolean isBlockPresent(long ptr, int x, int y, int z);
    private static native void tickAndRandomTickBlock(long ptr, int x, int y, int z);

    public static final LeafTickScheduler INSTANCE = new LeafTickScheduler();

    public final List<ScheduledTick> planned;
    public final List<ScheduledTick> scheduled;

    public LeafTickScheduler()
    {
        this.planned = new ArrayList<ScheduledTick>();
        this.scheduled = new ArrayList<ScheduledTick>();
    }

    public void schedule(NativeBlockSource world, int x, int y, int z, int delay)
    {
        this.planned.add(new ScheduledTick(world, x, y, z, delay));
    }

    public void tick()
    {
        if(!this.planned.isEmpty())
        {
            this.scheduled.addAll(this.planned);
            this.planned.clear();
        }
        if(this.scheduled.size() > 0)
        {
            Iterator<ScheduledTick> iterator = scheduled.iterator();
            while(iterator.hasNext())
            {
                ScheduledTick st = iterator.next();
                if(--st.tick <= 0)
                {
                    iterator.remove();
                    if(isBlockPresent(st.world.getPointer(), st.x, st.y, st.z))
                    {
                        int id = st.world.getBlockId(st.x, st.y, st.z);
                        if(id == 18 || id == 161)
                        {
                            tickAndRandomTickBlock(st.world.getPointer(), st.x, st.y, st.z);
                        }
                    }
                }
            }
        }
    }

    private static final class ScheduledTick {
        
        public final NativeBlockSource world;
        public final int x;
        public final int y;
        public final int z;
        public int tick;

        public ScheduledTick(NativeBlockSource world, int x, int y, int z, int tick)
        {
            this.world = world;
            this.x = x;
            this.y = y;
            this.z = z;
            this.tick = tick;
        }

    }

}

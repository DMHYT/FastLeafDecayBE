#ifndef FASTLEAFDECAY_CONFIG_H
#define FASTLEAFDECAY_CONFIG_H


class FLDConfig {
    public:
    static int minimumDecayTime;
    static int maximumDecayTime;
};
class FLDHandler {
    public:
    static int baseDecayTime;
    static int randomizationTime;
    static void update();
};


#endif //FASTLEAFDECAY_CONFIG_H
#pragma once

#include "CommonType.h"
#include "ZTEGraph.h"

namespace ZTE_crb {

    class ZTEGenetic : public ZTEGraph{
    public:
        ZTEGenetic() {};
        ~ZTEGenetic() {};
        ZTEGenetic(int _geneticSize, int _generations, int _maxVexNum = 9,
                   double _crossoverRate = 0.1, double _mutationRate = 0.05) :
                           geneticSize(_geneticSize),
                           generations(_generations),
                           crossoverRate(_crossoverRate),
                           mutationRate(_mutationRate) { maxVexNum = _maxVexNum; };

        void InitGenetic();
        void Evolution();

    protected:
        std::vector <Path> geneticGroup;
        int geneticSize;
        int generations;
        double crossoverRate;
        double mutationRate;

        void Crossover();
        void Mutation();

        Path Exchange(const Path &path1, const Path &path2, int pos);
        Path Variation(const Path &path, Vex target, Vex target2);

        Vex FindNearestVex(const Path &path, Vex vex, Path &shortcut);

    };

}
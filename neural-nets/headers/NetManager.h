#pragma once

#include "NeuralNet.h"

class NetManager {
private:
    NeuralNet* nets;
    std::pair<float, NeuralNet*>* scoreNetPairs;
    int numNets;

    int hiddenLayerSize;

public:
    NetManager();
    NetManager(const int& numNets, const int& hiddenLayerSize);
    ~NetManager();

    void initialize(const int& numNets, const int& hiddenLayerSize);

    void setNumNets(int numNets) { this->numNets = numNets; };
    void setHiddenLayerSize(int hiddenLayerSize) { this->hiddenLayerSize = hiddenLayerSize; };

    void keepScore(const float& score, const int& index);
    void selectAndMutateSurvivors(int numParents);

    NeuralNet& operator[](const int& index);
};
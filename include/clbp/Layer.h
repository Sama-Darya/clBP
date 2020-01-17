#pragma once


#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <ctgmath>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <fstream>
#include <iostream>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <numeric>
#include <vector>

#include "Neuron.h"

class Layer {
public:
    Layer(int _nNeurons, int _nInputs);

    ~Layer();

    void setInputs(const double *_inputs); // only for the first layer
    void initLayer(int _layerIndex, Neuron::weightInitMethod _wim, Neuron::biasInitMethod _bim, Neuron::actMethod _am);
    void calcOutputs();
    double getOutput(int _neuronIndex);
    double getSumOutput(int _neuronIndex);
    void propInputs(int _index, double _value);
    /*this is for hidden and output layers (not input)*/
    void printLayer();
    void propError(int _neuronIndex, double _nextSum);
    int getnNeurons();
    void setlearningRate(double _learningRate);
    double getError(int _neuronIndex);
    double getGlobalError(int _neuronIndex);
    double getWeights(int _neuronIndex, int _weightIndex);
    double getInitWeight(int _neuronIndex, int _weightIndex);
    double getWeightChange();
    double getWeightDistance();
    void setGlobalError(double _globalError);
    void setError(double _leadError);
    void updateWeights();
    void saveWeights();
    void snapWeights(); // This one just saves the final weights
    // i.e. overwrites them

    Neuron *getNeuron(int _neuronIndex);

private:
    int nNeurons = 0;
    int nInputs = 0;
    const double *inputs = 0;
    Neuron **neurons = 0;
    double learningRate = 0;
    double weightChange=0;
    double globalError = 0;
    int printInfo = 1;
    int myLayerIndex = 0;

};

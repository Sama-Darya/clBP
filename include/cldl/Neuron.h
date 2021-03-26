#pragma once
#include <ctgmath>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <numeric>
#include <vector>

using namespace std;
class Neuron {
public:
    Neuron(int _nInputs, int _nInternalErrors);
    ~Neuron();
    void setInternalError(int _internalErrorIndex, double _sumValue);
    double getInternalErrors(int _internalErrorIndex);
    enum biasInitMethod {B_NONE = 0, B_RANDOM = 1};
    enum weightInitMethod {W_ZEROS = 0, W_ONES = 1, W_RANDOM = 2};
    enum actMethod {Act_Sigmoid = 0, Act_Tanh = 1, Act_NONE = 2};
    void initNeuron(int _neuronIndex, int _layerIndex, weightInitMethod _wim, biasInitMethod _bim, actMethod _am);
    void setLearningRate(double _learningRate);
    void setInput(int _index, double _value);
    void propInputs(int _index, double _value);
    int calcOutput(int _layerHasReported);
    void setErrorInputsAndCalculateInternalError(int _inputIndex, double _value, int _internalErrorIndex);
    void updateWeights();
    double doActivation(double _sum);
    double doActivationPrime(double _input);
    double getOutput();
    double getSumOutput();
    double getWeights(int _inputIndex);
    double getInitWeights(int _inputIndex);
    double getWeightChange();
    double getMaxWeight();
    double getMinWeight();
    double getSumWeight();
    double getWeightDistance();
    int getnInputs();
    void saveWeights();
    void printNeuron();
    inline void setWeight(int _index, double _weight) {
        assert((_index >= 0) && (_index < nInputs));
        weights[_index] = _weight;
    }

private:
    // initialisation:
    int nInputs = 0;
    int myLayerIndex = 0;
    int myNeuronIndex = 0;

    double *initialWeights = nullptr;
    double learningRate = 0;

    double *inputErrors = nullptr;
    int nInternalErrors = 0;
    double *internalErrors = nullptr;
    bool *internalErrorIsSet = nullptr;
    int countInputErrors = 0;

    int iHaveReported = 0;
    double *inputs = nullptr;
    double bias = 0;
    double sum = 0;
    double output = 0;

    double *weights = nullptr;
    double weightSum = 0;
    double maxWeight = 1;
    double minWeight = 1;
    double weightChange = 0;
    double weightsDifference = 0;
    int actMet = 0;
};

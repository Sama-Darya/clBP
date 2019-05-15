#include "clbp/Neuron.h"

#include <iostream>
#include <ctgmath>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <fstream>

using namespace std;

Neuron::Neuron(int _nInputs)
{
     nInputs=_nInputs;
     weights = new double[nInputs];
     initialWeights = new double[nInputs];
     inputs = new double[nInputs];
}

Neuron::~Neuron(){
    delete [] weights;
    delete [] initialWeights;
    delete [] inputs;
}

void Neuron::setInput(int _index,  double _value) {
    /* the seInput function sets one input value at the given index,
     * it has to be implemented in a loop inside the layer class to set
     * all the inputs associated with all the neurons in that layer*/
    assert((_index>=0)&&(_index<nInputs));
    /*checking _index is a valid int, non-negative and within boundary*/
    inputs[_index] = _value;
}

void Neuron::propInputs(int _index,  double _value){
    /*works like setInput function expect it only applies
     * to the neurons in the hidden and output layers
     * and not the input layer*/
    assert((_index>=0)&&(_index<nInputs));
    inputs[_index] = _value;
}

void Neuron::initWeights(weightInitMethod _wim, biasInitMethod _bim){
    for (int i=0; i<nInputs; i++){
        switch (_wim){
        case W_ZEROS:
            weights[i]=0;
            break;
        case W_ONES:
            weights[i]=1;
            break;
        case W_RANDOM:
            weights[i]=((double)rand()/RAND_MAX);
             /* rand function generates a random function between
              * 0 and RAND_MAX, after the devision the weights are
              * set to a value between 0 and 1 */
        }
        initialWeights[i]=weights[i];

        //cout<<"INITIAL W: "<< initialWeights[i]<< endl;
        //saves the initial weights
    }
    switch (_bim){
    case B_NONE:
        bias=0;
        break;
    case B_RANDOM:
        bias=((double)rand()/RAND_MAX);
        break;
    }
}

void Neuron::calcOutput(){
    double* inputsp= inputs;
    double* weightsp= weights;
        /* making copies of the pointers for the scope of this
     * funciton so that the original pinters are unchanged and can
     * be used as a reference in other functiond simultaneously */
    sum=0;
    for (int i=0; i<nInputs; i++){
        double input= *inputsp;
        double weight= *weightsp;
        sum += input * weight;
        inputsp++;
        weightsp++;
    }
    sum += bias;
    doActivation(sum);
}

double Neuron::getOutput(){
    return (output);
}

double Neuron::getSumOutput(){
    return (sum);
}

double Neuron::doActivation(double _sum){
    output=1/(1+(exp(-_sum))) - 0.5;
    return (output);
}

double Neuron::doActivationPrime(double _input){
  return exp(-_input) / pow((exp(-_input) + 1), 2);
}

void Neuron::setLearningRate(double _learningRate){
    learningRate=_learningRate;
}

void Neuron::setError(double _leadError){

    error = _leadError * doActivationPrime(sum);
    /*might take a different format to propError*/
}

void Neuron::propError(double _nextSum){
    error = _nextSum; //* doActivationPrime(sum);
    //cout<< "_nextSum was: "<< _nextSum << "and dSigmadt is: " << doActivationPrime(sum) <<endl;
}

void Neuron::updateWeights(){
    for (int i=0; i<nInputs; i++){
        weights[i] += learningRate * (error * inputs[i]); //
        if (error != 0){
            cout<< "Neuron: weight: " << weights[i] << "  Neuron: error: " << error << "  Neuron: input: " << inputs[i] << endl;
        }
    }
}

double Neuron::getWeightChange(){
    double weightChange =0;
    double weightsDifference =0;
    for (int i=0; i<nInputs; i++){
        weightsDifference = weights[i] - initialWeights[i];
        weightChange += weightsDifference * weightsDifference;
    }
    cout<< "Neuron: WeightChange is: " << weightChange << endl;
    return weightChange;
}

double Neuron::getError(){
    return (error);
}

int Neuron::getnInputs(){
    return (nInputs);
}

double Neuron::getWeights(int _inputIndex){
    assert((_inputIndex>=0)&&(_inputIndex<nInputs));
    return (weights[_inputIndex]);
}

double Neuron::getInitWeights(int _inputIndex){
    assert((_inputIndex>=0)&&(_inputIndex<nInputs));
    return (initialWeights[_inputIndex]);
}

void Neuron::saveWeights(string _fileName){
    std::ofstream Icofile;
    Icofile.open(_fileName, fstream::app);
    for (int i=0; i<nInputs; i++){
        Icofile << weights[i] << " " ;
    }
    Icofile << "\n";
    Icofile.close();
}

void Neuron::printNeuron(){
    cout<< "\t \t This neuron has " << nInputs << " inputs:";
    for (int i=0; i<nInputs; i++){
        cout<< " " << inputs[i];
    }
    cout<<endl;
    cout<< "\t \t The weights for those inputs are:";
    for (int i=0; i<nInputs; i++){
        cout<< " " << weights[i];
    }
    cout<<endl;
    cout<< "\t \t The bias of the neuron is: " << bias << endl;
    cout<< "\t \t The sum and output of this neuron are: " << sum << ", " << output << endl;
}






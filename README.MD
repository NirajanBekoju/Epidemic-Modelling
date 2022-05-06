# Epidemic Modelling with SIR Model

## Abstract
([Compartmental Model in Epidemiology](https://en.wikipedia.org/wiki/Compartmental_models_in_epidemiology#The_SIR_model)
)
Epidemic modelling is the mathematical model to illustrate the spread of epidemic disease. We have use SIR model in order to study the epidemic disease transmission. SIR model is a compartmental model in epidemiology. In this model, the population is assigned to compartments with labels - for example :- S, I or R(SUSCEPTIBLE, INFECTIOUS or RECOVERED). People may progress between compartments. 

SIR model is one of the simplest compartmental models, and many models are derivatives of this basic form. The model consists of three compartments:-
1. S : The number of susceptible individuals. When a susceptible and an infectious come into "infectious contact", the susceptible individual contracts the disease and transitionsto the infectious compartment.
2. I : The number of infectious individuals. These are individuals who have been infected and are capable of infecting susceptible individuals.
3. R : The number of removed(and immuned) or deceased individuals. These are individuals who have been infected and have either recovered from the disease and entered the removed compartment, or died. it is assumed that the number of deaths is negligible with respect to the total population. This compartment may also be called "recoverd" or "ressistant".


## Implementation
We have first performed the mathematical model of the epidemic disease as show in the figure below.
Then, we took the data on various factor which are explained in ([Data Analysis](https://github.com/NirajanBekoju/Epidemic-Modelling/blob/master/Data%20Analysis.ipynb))

![Epidemic Modelling](https://github.com/NirajanBekoju/Epidemic-Modelling/blob/master/epidemic_modelling.png?raw=true)

## To Run Locally
To run locally, you mush have installed g++ Compiler(Used Version : 9.3.0), OPENGL library for mathematical modelling and Python3 for the data analysis part.


**Clone the repository**
```
git clone https://github.com/NirajanBekoju/Epidemic-Modelling
```

**Create a virtual environment and activate it**
```
virtualenv venv
source ./venv/bin/activate
```

**Install all requirements from requirements.txt**
```
pip install -r requirements.txt
```

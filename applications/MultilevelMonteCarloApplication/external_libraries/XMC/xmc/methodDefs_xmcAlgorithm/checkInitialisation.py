def checkInitialisationMC(XMCAlgorithm):
    """
    Method checking all attributes of different classes are correctly set to run Monte Carlo algorithm (both standard and asynchronous).
    """

    solverWrapperDictionary = XMCAlgorithm.monteCarloSampler.indexConstructorDictionary[
            "samplerInputDictionary"]["solverWrapperInputDictionary"]
    positionMaxNumberIterationsCriterion=XMCAlgorithm.positionMaxNumberIterationsCriterion
    tolerances=XMCAlgorithm.stoppingCriterion.tolerances()
    # perform checks
    checkInitialisationSolverWrapper(solverWrapperDictionary)
    if ("asynchronous" in solverWrapperDictionary):
        if (solverWrapperDictionary["asynchronous"] is True):
            checkMaxNumberIterationsCriterion(positionMaxNumberIterationsCriterion,tolerances)

def checkInitialisationCMLMC():
    pass

def checkInitialisationAMLMC():
    pass

def checkInitialisationMLMC(XMCAlgorithm):
    """
    Method checking all attributes of different classes are correctly set to run Multilevel Monte Carlo algorithm (both standard and asynchronous).
    """

    solverWrapperDictionary = XMCAlgorithm.monteCarloSampler.indexConstructorDictionary[
            "samplerInputDictionary"]["solverWrapperInputDictionary"]
    positionMaxNumberIterationsCriterion=XMCAlgorithm.positionMaxNumberIterationsCriterion
    tolerances=XMCAlgorithm.stoppingCriterion.tolerances()
    # perform checks
    checkInitialisationSolverWrapper(solverWrapperDictionary)
    if ("asynchronous" in solverWrapperDictionary):
        if (solverWrapperDictionary["asynchronous"] is True):
            checkMaxNumberIterationsCriterion(positionMaxNumberIterationsCriterion,tolerances)

def checkInitialisationSolverWrapper(solverWrapperDictionary):
    """
    Method checking solver wrapper keys are correctly set. A required key is outputBatchSize, which is needed to organize the quantities of interest into sublists (of future objects). For this reason, outputBatchSize must be smaller than or equal to the total number of quantities of interest. It is required if areSamplesSplit() is true.
    """

    sql = 1 ; ncq = 0 ; nq = 1 # default values
    if "outputBatchSize" in solverWrapperDictionary:
        sql = solverWrapperDictionary["outputBatchSize"]
    else:
        warnings.warn("outputBatchSize not defined in solverWrapper dictionary. The default value of 1 will be considered.")
    if "numberCombinedQoi" in solverWrapperDictionary:
        ncq = solverWrapperDictionary["numberCombinedQoi"]
    else:
        warnings.warn("numberCombinedQoi not defined in solverWrapper dictionary. The default value of 0 will be considered.")
    if "numberQoI" in solverWrapperDictionary:
        nq = solverWrapperDictionary["numberQoI"]
    else:
        warnings.warn("numberQoI not defined in solverWrapper dictionary. The default value of 1 will be considered.")

    if (sql > (nq+ncq)):
        raise Exception ("solverWrapperDictionary: outputBatchSize exceeding maximum dimension. Set a value <= numberQoI + numberCombinedQoI.")

def checkMaxNumberIterationsCriterion(positionMaxNumberIterationsCriterion,tolerances):
    """
    Method checking maximum number of iterations is set and is the last entry of MonoCriteriaDictionary, which is required for consistency.
    """

    if (positionMaxNumberIterationsCriterion is not None):
        if (len(tolerances) == (positionMaxNumberIterationsCriterion + 1)):
            pass
        else:
            raise Exception ("Number of monoCriteria defined in monoCriteriaDictionary and positionMaxNumberIterationsCriterion defined in xmcAlgorithmDictionary not consistent. Should be positionMaxNumberIterationsCriterion = number monoCriteria and the monoCriterion defining the maximum number of iterations set as last entry of monoCriteriaDictionary.")
    else:
        raise Exception ("positionMaxNumberIterationsCriterion not set in xmcDictionary. Set it in order to run the asynchronous framework.")
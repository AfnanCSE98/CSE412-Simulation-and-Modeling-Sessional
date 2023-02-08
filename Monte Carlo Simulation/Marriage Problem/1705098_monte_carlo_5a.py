import numpy as np
import matplotlib.pyplot as plt


def marriage_problem(n,S):
    X = []
    Y = []
    for s in S:
        for m in range(1,n):
            success_count = 0
            X.append(m)
            for i in range(10000):                        
                # initialize the population with uniform random numbers 
                population = np.random.uniform(0,1,n)
                # print(population)
                if m == 0:
                    training_best = []
                else:
                    training_population = population[:m]
                    # print(training_population)
                    # get the population without the training population
                    interview_population = population[m:]
                    training_best = np.max(training_population)
                # print(training_best)
                selected_candidate = -1
                for j in interview_population:
                    if j > training_best:
                        selected_candidate = j
                        break
                if selected_candidate == -1:
                    selected_candidate = population[-1]
                # print(selected_candidate)
                # check if the selected candidate is in the top s candidates of the total population
                population = np.sort(population)
                population = population[::-1]
                
                if selected_candidate in population[:s]:
                    # print("Success")
                    success_count += 1
                                
            success_rate = success_count/10000
            Y.append(success_rate)
        plt.plot(X,Y)
        plt.xlabel("Sample Size")
        plt.ylabel("Success Rate")
        plt.title("Success Rate vs Sample Size for n=100, s = " + str(s))
        plt.show()
        X = []
        Y = []



n=100
S=[1,3,5,10] 
marriage_problem(n,S)

        
        
import random

def monte_carlo_chain_reaction(n, p0, pi, num_iteration):
    # Initialize counters for each outcome
    count_0 = 0
    count_1 = 0
    count_2 = 0
    count_3 = 0
    count_4 = 0

    p1 = p0 + pi[0]
    p2 = p1 + pi[1]
    p3 = p2 + pi[2]
    
    # Repeat simulation n times
    for i in range(num_iteration):
        num_neutrons = 1  # Initialize number of neutrons to 1

        for j in range(n):
            # determine number of neutrons produced for each neutron in each generation
            new_neutrons = 0
            for k in range(num_neutrons):
                r = random.uniform(0, 1)
                if r < p0:
                    new_neutrons += 0
                elif r < p1:
                    new_neutrons += 1
                elif r < p2:
                    new_neutrons += 2
                elif r < p3:
                    new_neutrons += 3
                else:
                    new_neutrons += 4
            num_neutrons = new_neutrons            
                    
        # Update the counters based on the final number of neutrons
        if num_neutrons == 0:
            count_0 += 1
        elif num_neutrons == 1:
            count_1 += 1
        elif num_neutrons == 2:
            count_2 += 1
        elif num_neutrons == 3:
            count_3 += 1
        else:
            count_4 += 1
    
    # Calculate the probabilities and return as a list
    prob_0 = count_0 / num_iteration
    prob_1 = count_1 / num_iteration
    prob_2 = count_2 / num_iteration
    prob_3 = count_3 / num_iteration
    prob_4 = count_4 / num_iteration
    result = [prob_0, prob_1, prob_2, prob_3, prob_4]
    print("Generation: ", n)
    print("Probability of 0 neutrons: ", result[0])
    print("Probability of 1 neutrons: ", result[1])
    print("Probability of 2 neutrons: ", result[2])
    print("Probability of 3 neutrons: ", result[3])
    print("Probability of 4 neutrons: ", result[4])

n = int(input("Enter the number of generations: "))
p0 = 0.4825
pi = [(0.2126) * (0.5893) ** (i-1) for i in range(1, 4)]
prob_sum = sum(pi)+p0
print(prob_sum)
if(prob_sum != 1):
    p0 = p0 + (1 - prob_sum)
# print(p0)
num_iteration = 10000  # Number of simulations to run
result = monte_carlo_chain_reaction(n, p0, pi, num_iteration)

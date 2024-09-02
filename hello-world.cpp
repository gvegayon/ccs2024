#include "epiworld.hpp"

int main() {
    // Initializing one of the existing models.
    epiworld::epimodels::ModelSIR<> model(
        "Flu", // Name
        .01,   // Initial infected
        .2,    // Transmission rate
        .14    // Recovery rate
        );

    // Adding agents to the model
    model.agents_smallworld(
        100000, // Population size
        10,     // Number of contacts
        false,  // Directed = false
        0.01    // Rewiring probability
        );

    // Running and printing!
    model.run(100, 771);
    model.print();

    return 0;
}
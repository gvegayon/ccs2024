#include "epiworld.hpp"

using namespace epiworld;

const static double mutrate = 0.01;

int main() {

    // Initializing one of the existing models.
    // In this case, network SEIR.
    epimodels::ModelSEIR<> model(
        "Covid-19",
        0.01,
        0.3,
        7.0,
        1.0/7.0
    );
    
    // Random network population
    model.seed(331);
    model.agents_smallworld(2e5, 10, false, 0.1);

    // Mutation function
    auto mutate = [](Agent<> * agent, Virus<> & virus, Model<> * model) -> bool {
        return mutrate > model->runif();
    };

    model.get_virus(0).set_mutation(mutate);

    // Designing intervention: Lower transmission
    // rate by means of masking
    GlobalFun<> mask_up = [](Model<> * model) {
        
        std::vector<int> tmatrix;
        model->get_db().get_today_transition_matrix(tmatrix);

        // Col-major, it is second row
        int new_infected = tmatrix[4 * 2 + 1]; 
        printf("New infected: %d\n", new_infected);
        if (new_infected > 5000)
            model->set_param("Transmission rate",  0.00);
        if (new_infected < 1000)
            model->set_param("Transmission rate",  0.30);
        
    };

    model.add_globalevent(mask_up, "Mask up");

    // Running the model
    model.run(50, 221);
    model.print();

    // Saving the data
    model.write_data(
        "",
        "",
        "",
        "",
        "total_hist.tsv",
        "",
        "transitions.tsv",
        "repnum.tsv",
        ""
    );

    return 0;

}
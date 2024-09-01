#include "epiworld.hpp"

using namespace epiworld;

// Some constants
const static double p_mutate = 0.0025;
const static int max_int = std::numeric_limits<int>::max();

EPI_NEW_MUTFUN(flumutates, int)
{

    if (p_mutate < m->runif())
    {
        // Creating new random sequence
        v.set_sequence(static_cast<int>(m->runif() * max_int));

        // Changing transmissibility (max 0.3)
        v.set_prob_infecting(m->runif() * .3);

        return true;
    }

    return false;

}

int main() {

    // Initializing one of the existing models.
    // In this case, network SEIR.
    epimodels::ModelSEIRCONN<> model(
        "Covid-19",
        2e5,
        0.0001, // ~20 cases
        5,
        0.3,
        7.0,
        1.0/7.0
    );

    // VIRUS DESIGN --------------------------------
    Virus<> flu("Flu");
    flu.set_incubation(5.0);
    flu.set_prob_infecting(0.2);
    flu.set_prob_recovery(1.0/7.0);

    // Adding mutation
    flu.set_mutation(flumutates);

    // How will it be distributed
    flu.set_distribution(
        distribute_virus_randomly<>(20, false)
        );
    
    // Adding virus to the model
    flu.set_state(1, 3);
    model.add_virus(flu);

    // Designing intervention: Lower transmission
    // rate by means of masking
    GlobalFun<> full_isolation = [](Model<> * model) {
        
        std::vector<int> tmatrix;
        model->get_db().get_today_transition_matrix(tmatrix);

        // Col-major, it is second row
        int new_exposed = tmatrix[4]; 
        if (new_exposed > 1000)
            model->set_param("Contact rate",  0.3);
        if (new_exposed < 100)
            model->set_param("Contact rate",  5);
        
    };

    model.add_globalevent(full_isolation, "Full isolate");

    // Running the model
    model.run(100, 221);
    model.print();

    // Saving the data
    model.write_data(
        "",
        "",
        "",
        "",
        "total_hist.tsv",
        "transmissions.tsv",
        "transitions.tsv",
        "repnum.tsv",
        ""
    );

    return 0;

}
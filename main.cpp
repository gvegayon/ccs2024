#include "epiworld.hpp"

using namespace epiworld;

// Some constants
const static double p_mutate = 0.001;
const static int max_int = std::numeric_limits<int>::max();

EPI_NEW_MUTFUN(flumutates, int)
{

    if (p_mutate > m->runif())
    {
        // Creating new random sequence and updating
        // transmission probability
        double new_pinfect = m->runif() * 0.7;
        v.set_sequence(static_cast<int>(new_pinfect * max_int));
        v.set_prob_infecting(new_pinfect);
        v.set_name("flu-variant-" + std::to_string(new_pinfect));

        return true;
    }

    return false;

}

std::vector<int> tmatrix;
EPI_NEW_GLOBALFUN(full_isolation, int)
{
        
    m->get_db().get_today_transition_matrix(tmatrix);
    int new_exposed = tmatrix[4]; 
    
    if (new_exposed > 1000)
        m->set_param("Contact rate",  0.3);
    if (new_exposed < 100)
        m->set_param("Contact rate",  10);

};

int main() {

    // Initializing one of the existing models.
    // In this case, network SEIR.
    epimodels::ModelSEIRCONN<> model(
        "Covid-19",
        2e5,    // Population size
        0.0001, // ~20 cases
        10,      // Contact rate
        0.3,    // Transmission rate
        7.0,    // Mean incubation
        1.0/7.0 // Recovery rate
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

    // Tool design ----------------------------------
    Tool<> vaccine("Vaccine");
    vaccine.set_transmission_reduction(0.3);
    vaccine.set_recovery_enhancer(0.9);
    vaccine.set_distribution(
        distribute_tool_randomly<>(0.3, true)
    );

    model.add_tool(vaccine);

    // Designing intervention: isolation --------------------
    model.add_globalevent(full_isolation, "Full isolate");

    // Running the model
    model.run(180, 221);
    model.print();

    // Saving the data
    model.write_data(
        "res/virus_info.tsv",
        "res/virus_hist.tsv",
        "res/tool_info.tsv",
        "res/tool_hist.tsv",
        "res/total_hist.tsv",
        "res/transmissions.tsv",
        "res/transitions.tsv",
        "res/repnum.tsv",
        "res/gentime.tsv"
    );

    return 0;

}
# epiworld(C++ \| R \| Py): A fast multi-language library for
epidemiological agent-based models


## From the abstract

I n this presentation, we will describe the main software design
components that make epiworld so flexible and fast, discuss the
challenges and decisions behind some of its key components, and provide
an extended example illustrating its use. We will show how epiworld can
be used to build a complex outbreak model with a large networked
population featuring an evolving virus that generates multiple variants,
heterogeneous susceptibility and recovery rates across the population,
and a dynamic non-pharmaceutical intervention that triggers according to
the n

``` bash
./main.o
```

    _________________________________________________________________________
    |Running the model...
    New infected: 266
    |New infected: 1020
    ||New infected: 2507
    |New infected: 3933
    ||New infected: 5108
    |New infected: 5882
    ||New infected: 4957
    |New infected: 4336
    ||New infected: 3729
    |New infected: 3003
    ||New infected: 2716
    |New infected: 2314
    |New infected: 2040
    ||New infected: 1687
    |New infected: 1460
    ||New infected: 1211
    |New infected: 1109
    ||New infected: 938
    |New infected: 727
    ||New infected: 1489
    |New infected: 2229
    ||New infected: 3019
    |New infected: 3761
    ||New infected: 4321
    |New infected: 4682
    |New infected: 4956
    ||New infected: 5060
    |New infected: 5219
    ||New infected: 4456
    |New infected: 3825
    ||New infected: 3349
    |New infected: 2712
    ||New infected: 2373
    |New infected: 2079
    ||New infected: 1741
    |New infected: 1477
    ||New infected: 1285
    |New infected: 1118
    |New infected: 947
    ||New infected: 785
    |New infected: 1198
    ||New infected: 1491
    |New infected: 2024
    ||New infected: 2389
    |New infected: 2662
    ||New infected: 2812
    |New infected: 2994
    ||New infected: 3131
    |New infected: 3128
    || done.
    New infected: 3195
    | done.
    ________________________________________________________________________________
    ________________________________________________________________________________
    SIMULATION STUDY

    Name of the model   : Susceptible-Exposed-Infected-Removed (SEIR)
    Population size     : 200000
    Agents' data        : (none)
    Number of entities  : 0
    Days (duration)     : 50 (of 50)
    Number of viruses   : 1
    Last run elapsed t  : 289.00ms
    Last run speed      : 34.58 million agents x day / second
    Rewiring            : off

    Global events:
     - Mask up (runs daily)

    Virus(es):
     - Covid-19

    Tool(s):
     (none)

    Model parameters:
     - Incubation days   : 7.0000
     - Recovery rate     : 0.1429
     - Transmission rate : 0.3000

    Distribution of the population at time 50:
      - (0) Susceptible : 198000 -> 43489
      - (1) Exposed     :   2000 -> 21661
      - (2) Infected    :      0 -> 18123
      - (3) Removed     :      0 -> 116727

    Transition Probabilities:
     - Susceptible  0.97  0.03  0.00  0.00
     - Exposed      0.00  0.86  0.14  0.00
     - Infected     0.00  0.00  0.86  0.14
     - Removed      0.00  0.00  0.00  1.00

``` r
library(data.table)
sim_res <- fread("total_hist.tsv")
sim_res[, incidence := counts - shift(counts, 1, fill = 0), by = state]
library(ggplot2)
sim_res[state %in% c("Exposed", "Infected")] |>
  ggplot(aes(x = date, y = incidence, color = state)) +
  geom_line() +
  labs(title = "Epidemiological model",
       x = "Date",
       y = "Count")
```

![](README_files/figure-commonmark/unnamed-chunk-2-1.png)

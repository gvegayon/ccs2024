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
    Running the model...
    ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| done.
     done.
    ________________________________________________________________________________
    ________________________________________________________________________________
    SIMULATION STUDY

    Name of the model   : Susceptible-Exposed-Infected-Removed (SEIR) (connected)
    Population size     : 200000
    Agents' data        : (none)
    Number of entities  : 0
    Days (duration)     : 100 (of 100)
    Number of viruses   : 13819
    Last run elapsed t  : 535.00ms
    Last run speed      : 37.36 million agents x day / second
    Rewiring            : off

    Global events:
     - Update infected individuals (runs daily)
     - Full isolate (runs daily)

    Virus(es):
     - Covid-19
     - Flu
     ...and 13817 more variants...

    Tool(s):
     (none)

    Model parameters:
     - Avg. Incubation days : 7.0000
     - Contact rate         : 0.3000
     - Prob. Recovery       : 0.1429
     - Prob. Transmission   : 0.3000

    Distribution of the population at time 100:
      - (0) Susceptible : 199960 -> 169129
      - (1) Exposed     :     40 -> 2345
      - (2) Infected    :      0 -> 3166
      - (3) Recovered   :      0 -> 25360

    Transition Probabilities:
     - Susceptible  1.00  0.00  0.00  0.00
     - Exposed      0.00  0.85  0.15  0.00
     - Infected     0.00  0.00  0.86  0.14
     - Recovered    0.00  0.00  0.00  1.00

``` r
library(data.table)
incidence <- fread("transitions.tsv")
incidence <- incidence[from == "Susceptible" & to == "Exposed"]
library(ggplot2)
ggplot(incidence, aes(x = date, y = counts)) +
  geom_line() +
  labs(
    title = "Daily incidence",
    x = "Date",
    y = "Count"
    ) +
  scale_y_log10()
```

    Warning in scale_y_log10(): log-10 transformation introduced infinite values.

![](README_files/figure-commonmark/unnamed-chunk-2-1.png)

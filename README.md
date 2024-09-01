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
    Days (duration)     : 180 (of 180)
    Number of viruses   : 137
    Last run elapsed t  : 748.00ms
    Last run speed      : 48.10 million agents x day / second
    Rewiring            : off

    Global events:
     - Update infected individuals (runs daily)
     - Full isolate (runs daily)

    Virus(es):
     - Covid-19
     - Flu
     ...and 135 more variants...

    Tool(s):
     - Vaccine

    Model parameters:
     - Avg. Incubation days : 7.0000
     - Contact rate         : 0.3000
     - Prob. Recovery       : 0.1429
     - Prob. Transmission   : 0.3000

    Distribution of the population at time 180:
      - (0) Susceptible : 199960 -> 145499
      - (1) Exposed     :     40 -> 1210
      - (2) Infected    :      0 -> 1482
      - (3) Recovered   :      0 -> 51809

    Transition Probabilities:
     - Susceptible  1.00  0.00  0.00  0.00
     - Exposed      0.00  0.84  0.16  0.00
     - Infected     0.00  0.00  0.80  0.20
     - Recovered    0.00  0.00  0.00  1.00

``` r
library(data.table)
incidence <- fread("res/transitions.tsv")
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

``` r
virus_hist <- fread("res/transmissions.tsv")

# Total transmissions
daily_virus <- virus_hist[, .(count = .N), by = .(virus, date)]
daily_virus[, t_rate := as.double(gsub(".+-0\\.", "0.", virus))]
```

    Warning in eval(jsub, SDenv, parent.frame()): NAs introduced by coercion

``` r
daily_virus[is.na(t_rate), t_rate := fifelse(
  virus == "Covid-19", .3, .2
)]

daily_virus[, vlabel := fifelse(grepl("-0\\.", virus), "Flu-variant", virus)]

ggplot(daily_virus, aes(
  x = date, y = count, color = t_rate, group=t_rate)) +
  scale_color_distiller(palette="YlOrRd", direction = 1) +
  geom_line() +
  geom_point(aes(shape = vlabel)) +
  scale_y_log10() +
  theme_dark() +
  labs(
    color = "Transmission\nRate",
    shape = "Variant",
    x = "Step (time)",
    y = "Daily incidence (log10)"
  )
```

![](README_files/figure-commonmark/variants-1.png)

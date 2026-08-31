# Factor Models 📊

Asset-pricing models applied to the Nifty 50, moving from one factor to several. Each notebook estimates **per-stock** risk exposures by regressing a stock's daily excess return on one or more factor-return series, over a 5-year window.

```
Factor Models/
├── CAPM.ipynb           # Single factor: market. Beta, alpha, Security Market Line (multi-window)
├── Fama-French.ipynb    # Three factors: market + size (SMB) + value (HML)
└── (momentum — planned) # Carhart 4-factor: adds WML
```

Both notebooks share the same universe (the current 50 Nifty constituents), the same 5-year daily window, and the same method — a time-series regression per stock — so their per-stock outputs are directly comparable.

---

## CAPM vs. Fama-French — what the second factor set buys you

Running both on the identical 50 stocks and window lets us ask the core empirical question: **does adding size and value to the market factor explain stock returns better, and does it shrink the "alpha" CAPM leaves behind?**

| Metric (50 stocks, 5-year daily) | CAPM (1-factor) | Fama-French (3-factor) |
|---|---|---|
| Mean R² | 0.27 | **0.33** |
| Stocks with higher R² under FF3 | — | **50 / 50** |
| Mean market beta | 0.99 | 1.00 |
| Correlation of market betas across models | — | **0.985** |
| Mean \|alpha\| (annualised) | ~11.6% | ~11.0% |
| Stocks whose \|alpha\| shrank under FF3 | — | **28 / 50** |

Four things stand out:

**Market beta barely moves.** The market loadings from the two models correlate 0.985, with a mean absolute difference of just 0.04. Adding size and value doesn't distort how sensitive each stock is to the market — a stock's market beta is a robust quantity, and CAPM already captures it well.

**Three factors explain more variance — for every stock.** Mean R² rises from 0.27 to 0.33, and it improves for all 50 names, not just on average. Size and value carry genuine explanatory power for these stocks' daily co-movement beyond the market alone.

**Alphas shrink, but only modestly.** Mean absolute alpha falls slightly (~11.6% → ~11.0% annualised) and drops for 28 of 50 stocks. Some of what CAPM labelled "abnormal return" was really compensation for size/value exposure. But the alphas stay large — because their real inflation comes from **survivorship bias** (today's constituents applied backward) and the particular sample window, neither of which a three-factor model fixes.

**The value factor does real work; the size factor is weak here.** HML loads as theory predicts — deep-value cyclicals (ONGC, Coal India, Hindalco, Tata Steel, NTPC) load strongly positive, while growth/quality names (Eternal, Asian Paints, HUL, Nestlé) load negative. SMB is the weak link: the universe is 50 *large* caps, so "small" only means relatively smaller large-caps, and the size factor mostly picks up high-beta mid-tier names rather than a true small-cap premium.

---

## Caveats (both models)

- **Self-built factors from 50 large caps**, not the whole market — SMB especially is noisy. The IIM Ahmedabad India factor library (built from the full universe) is the more robust source, and a good next step for validation.
- **Static end-of-period sort** — size/value buckets are formed once (at the formation date) and applied across the whole 5-year history, which is look-ahead in the factor construction. A proper build rebalances annually with point-in-time data.
- **Survivorship bias** — using the current Nifty 50 backward over-represents past winners.
- **Equal-weighted buckets** (the real Fama-French uses value-weighting), **financials** (~40% of the index) whose book equity isn't comparable to industrials, **shallow/patchy yfinance fundamentals** (e.g. one or two book-equity values look wrong), and the **Tata Motors (TMPV) demerger-day** artifact, cleaned in CAPM but not yet in Fama-French.

These are learning-scale simplifications: the notebooks are built to show *how* the models work and *how they differ*, not to deliver a publication-grade factor study.

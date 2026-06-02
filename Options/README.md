# Options 📊

This folder covers the mathematical machinery of options — from basic payoffs through to Monte Carlo pricing of exotic contracts. Each notebook builds on the previous one, and the `.py` modules are shared across notebooks to avoid duplication.

---

## Structure

```
Options/
├── Options basic payoffs.ipynb       # Payoff intuition — the starting point
├── Geometric Brownian Motion.ipynb   # Stock price simulation
├── Black Scholes.ipynb               # Analytical pricing from scratch
├── Greeks.ipynb                      # Delta, Gamma, Vega, Theta
├── Monte Carlo Options Pricing.ipynb # MC pricing + Asian options
├── Options_basic_payoffs.py          # Reusable payoff functions
├── Geometric_Brownian_Motion.py      # Reusable GBM simulation engine
└── Black_Scholes.py                  # Reusable BS pricer (imported by Greeks & MC)
```

> **Run order:** Notebooks import from `.py` modules in the same folder. Run Jupyter from within the `Options/` directory, or set the kernel working directory to `Options/`.

---

## Notebooks

### 1. `Options basic payoffs.ipynb` — Payoff Diagrams & Covered Call
Builds intuition for vanilla options by computing and plotting profit profiles for all four basic positions, then constructs a Covered Call.

**What's covered:**
- Payoff functions for **Long Call**, **Long Put**, **Short Call**, **Short Put** (profit = payoff − premium)
- Payoff table across stock prices 1–100 (K = 50, premium = 10)
- 2×2 subplot grid of all four positions
- **Covered Call** — long stock + short call — capped upside profile

**Key insight:** The Covered Call caps profit at `premium + (K − cost_of_stock)` = 20 while retaining full downside — the classic income-vs-protection trade-off.

---

### 2. `Geometric Brownian Motion.ipynb` — Monte Carlo Stock Price Simulation
Implements the GBM stochastic process from scratch. The `Geometric_Brownian_Motion.py` module extracted here is the simulation engine used by the Monte Carlo pricer.

**The model:** `S(t) = S₀ · exp((μ − 0.5σ²)t + σW(t))`

**What's covered:**
- Discrete GBM via cumulative Brownian increments
- Simulation engine: `simulate_gbm()`, `RunSimulationEngine()`, `GetTerminalPrices()`
- Path plots and terminal price histograms at 100 / 1 000 / 10 000 runs
- Convergence of terminal distribution toward log-normal

**Parameters:** S₀ = 100, μ = 5%, σ = 20%, T = 1 year, N = 252 days

---

### 3. `Black Scholes.ipynb` — Analytical Pricing from Scratch
Derives and implements the Black-Scholes closed-form formula for European calls and puts, verifies Put-Call Parity, and analyses parameter sensitivity.

**The formula:** `C = S·N(d₁) − K·e^(−rT)·N(d₂)`

**What's covered:**
- `calculateD1`, `calculateD2`, `calculateCallOptionPrice`, `calculatePutOptionPrice`
- ATM pricing: C ≈ **10.45**, P ≈ **5.57** (S=K=100, σ=20%, r=5%, T=1yr)
- **Put-Call Parity** `C − P = S − K·e^(−rT)` verified to machine precision
- 4-panel sensitivity: call price vs σ, T, S, and r

**Key findings:**
- Call price increases monotonically with σ, T, and r
- Sensitivity to S is highest near the strike — where Delta is largest

---

### 4. `Greeks.ipynb` — Delta, Gamma, Vega, Theta
Implements all four first-order Greeks analytically and visualises them across a full range of stock prices. Imports `Black_Scholes.py` for d₁/d₂.

| Greek | Formula | Measures |
|---|---|---|
| Delta | N(d₁) | Option price sensitivity to S |
| Gamma | N'(d₁) / (S·σ·√T) | Rate of change of Delta |
| Vega | S·N'(d₁)·√T | Sensitivity to volatility |
| Theta | see formula | Time decay (per year) |

**What's covered:**
- All four Greeks computed across S = 1–200 (K = 100), plotted as 2×2 grid
- **Theta decay curve** — theta vs time to expiry with 3-month and 1-month markers; x-axis inverted to read left = near expiry

**Key insights:**
- Delta ≈ 0.637 ATM — option price moves ~63p for every ₹1 move in underlying
- Gamma and Vega both peak at-the-money — highest sensitivity to moves and vol changes
- Theta decay is non-linear and accelerates sharply inside the final month

---

### 5. `Monte Carlo Options Pricing.ipynb` — MC Pricing & Asian Options
Connects the GBM simulation engine to the Black-Scholes framework to price options numerically, then extends to path-dependent **Asian options** — contracts BS cannot price analytically.

**What's covered:**
- `CalculatePayoff()` — vectorised max(Sₜ − K, 0) over all paths
- `CalculateMonteCarloPrice()` — simulate paths via `GBM.RunSimulationEngine`, extract terminal prices, discount mean payoff: `price = E[payoff] · e^(−rT)`
- **Convergence plot** — MC price vs number of simulations (log scale) with BS analytical price as a red dashed benchmark
- Optimised terminal-only variant (no full path needed for European options)
- **Asian Call option** — replaces terminal price with path average `E[S̄]`, making it cheaper and less volatile than a vanilla call

**Convergence results (S=K=100, σ=20%, r=5%, T=1yr):**

| Simulations | MC Price |
|---|---|
| 10 | noisy |
| 1 000 | ~10–11 |
| 10 000 | ~10.4 |
| 100 000 | ~10.45 |
| 1 000 000 | ≈ 10.45 ✓ |

**Key insight:** MC converges to the BS price (~10.45) at ~100K paths. Asian options price lower than vanilla because averaging dampens the terminal payoff — useful when hedging average-price exposures.

---

## Module Reference

### `Black_Scholes.py`
| Function | Signature | Returns |
|---|---|---|
| `calculateD1` | `(S, K, r, T, sigma)` | float |
| `calculateD2` | `(sigma, T, d1)` | float |
| `calculateCallOptionPrice` | `(S, K, r, T, sigma)` | float |
| `calculatePutOptionPrice` | `(callPrice, S, K, r, T)` | float (via Put-Call Parity) |

### `Geometric_Brownian_Motion.py`
| Function | Signature | Returns |
|---|---|---|
| `simulate_gbm` | `(S0, mu, sigma, T, N)` | array of shape (N,) |
| `RunSimulationEngine` | `(sim_runs, S0, mu, sigma, T, N)` | array of shape (sim_runs, N) |
| `GetTerminalPrices` | `(paths)` | array of shape (sim_runs,) |

### `Options_basic_payoffs.py`
| Function | Signature | Returns |
|---|---|---|
| `CalculateLongCallPayoff` | `(stockPrice, strikePrice, premium)` | float |
| `CalculateLongPutPayoff` | `(stockPrice, strikePrice, premium)` | float |
| `CalculateShortCallPayoff` | `(stockPrice, strikePrice, premium)` | float |
| `CalculateShortPutPayoff` | `(stockPrice, strikePrice, premium)` | float |

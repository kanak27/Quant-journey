# Quant Journey 📈

A personal learning repository documenting my path into quantitative finance. Each notebook explores a core concept in financial data analysis and statistical modelling, applied to real Indian market data pulled live from Yahoo Finance.

---

## Repository Structure

```
Quant Journey/
├── Nifty50 Quant prep.ipynb          # Return distributions & descriptive stats
├── Covariance and Correlation.ipynb  # Portfolio diversification analysis
├── OLS.ipynb                         # OLS regression & hypothesis testing
├── PCA.ipynb                         # Principal component analysis
└── Options/
    ├── Options basic payoffs.ipynb   # Long/Short Call & Put, Covered Call
    ├── Geometric Brownian Motion.ipynb  # Monte Carlo stock price simulation
    ├── Black Scholes.ipynb           # BS pricing, Put-Call Parity, sensitivity
    ├── Greeks.ipynb                  # Delta, Gamma, Vega, Theta
    ├── Options_basic_payoffs.py      # Reusable module
    ├── Geometric_Brownian_Motion.py  # Reusable module
    └── Black_Scholes.py              # Reusable module (imported by Greeks.ipynb)
```

---

## Notebooks

### 1. `Nifty50 Quant prep.ipynb` — Return Distributions & Descriptive Statistics
The starting point. Downloads one year of Nifty 50 (^NSEI) index data and builds a ground-up understanding of return series.

**What's covered:**
- Computing **daily percentage returns** and **log returns** from closing prices
- Descriptive statistics: mean, variance, skewness, and excess kurtosis via `scipy.stats.describe`
- Building a **CDF from scratch** (rank-based) and overlaying the theoretical normal CDF
- Fitting a normal distribution to the return series with `scipy.stats.norm.fit`
- Visualising return histograms to inspect tail behaviour

**Key finding:** Nifty 50 daily returns show slight negative skew and excess kurtosis (~2.66), consistent with fat tails commonly observed in equity indices.

---

### 2. `Covariance and Correlation.ipynb` — Portfolio Diversification Analysis
Extends the single-index analysis to a 5-stock Nifty portfolio to understand co-movement between large-cap Indian equities.

**Stocks:** RELIANCE · HDFCBANK · TCS · INFY · ITC

**What's covered:**
- Downloading multi-ticker OHLCV data and computing daily returns for each stock
- Building a **covariance matrix** and **correlation matrix** from the return series
- Visualising both matrices as annotated **seaborn heatmaps**

**Key finding:** INFY and ITC show the lowest pairwise correlations with the rest of the basket, making them the most diversifying additions to a Nifty-heavy portfolio.

---

### 3. `OLS.ipynb` — Ordinary Least Squares Regression & Hypothesis Testing
Tests a simple predictive hypothesis: *does today's Nifty return predict tomorrow's?* Implements OLS both from scratch and via `scipy`.

**What's covered:**
- Constructing the **design matrix** and solving the normal equations manually: `β = (XᵀX)⁻¹Xᵀy`
- Cross-checking against `scipy.stats.linregress`
- Reporting slope, intercept, R², and p-value
- **One-sample t-test** to determine whether the mean daily return is significantly different from zero

**Key findings:**
- Slope ≈ −0.060, R² ≈ 0.004, p-value ≈ 0.35 → today's return has no statistically significant predictive power over tomorrow's
- Mean daily return is not significantly different from zero (t-stat ≈ −0.37, p ≈ 0.71), consistent with the weak-form Efficient Market Hypothesis

---

### 4. `PCA.ipynb` — Principal Component Analysis on Nifty Stocks
Applies dimensionality reduction to a 10-stock Nifty basket to uncover the latent risk factors driving co-movement.

**Stocks:** RELIANCE · HDFCBANK · TCS · INFY · ITC · HEROMOTOCO · COALINDIA · TATASTEEL · BRITANNIA · APOLLOHOSP

**What's covered:**
- Standardising returns with `sklearn.preprocessing.StandardScaler`
- Fitting `sklearn.decomposition.PCA` and inspecting components, explained variance, and singular values
- **Scree plot** with individual and cumulative explained variance (80% threshold line)
- **Biplot** of stock loadings on PC1 and PC2 to visualise how stocks cluster
- **Loadings heatmap** (first 6 PCs) to interpret which stocks drive each principal component

**Key findings:**
- PC1 explains ~29.6% of variance and loads negatively on all stocks — it is a broad **market factor**
- PC2 (~15.3%) captures a growth vs. defensive split, contrasting IT stocks (INFY, TCS) against industrials
- ~5 components are sufficient to explain ~80% of total variance in the basket

---

### 5. `Options/Options basic payoffs.ipynb` — Options Payoff Diagrams & Covered Call
Builds intuition for vanilla options by computing and plotting payoff profiles for all four basic positions, then constructs a Covered Call strategy.

**What's covered:**
- Implementing payoff functions for **Long Call**, **Long Put**, **Short Call**, and **Short Put** (profit = payoff − premium)
- Generating a payoff table across stock prices 1–100 (K = 50, premium = 10)
- Plotting all four payoffs as a 2×2 subplot grid
- Combining a **long stock position** with a **short call** to produce a **Covered Call** payoff

**Key insight:** The Covered Call caps profit at `premium + (K − cost_of_stock)` = 20, while retaining full downside exposure — illustrating the classic income-vs-protection trade-off.

---

### 6. `Options/Geometric Brownian Motion.ipynb` — Monte Carlo Stock Price Simulation
Implements the GBM stochastic process from scratch to simulate realistic stock price paths, forming the backbone of options pricing models.

**The model:** `S(t) = S₀ · exp((μ − 0.5σ²)t + σW(t))`

**What's covered:**
- Deriving the discrete GBM formula and implementing `simulate_gbm()` using cumulative Brownian increments
- Building a **simulation engine** that runs an arbitrary number of independent paths (100 / 1 000 / 10 000 runs)
- Plotting all simulated price paths and the resulting **terminal price histogram**
- Observing convergence toward a log-normal as simulation runs increase

**Parameters:** S₀ = 100, μ = 5%, σ = 20%, T = 1 year, N = 252 trading days

**Key insight:** The right-skewed terminal price distribution reflects the log-normal assumption embedded in GBM — the same assumption underpinning Black–Scholes.

---

### 7. `Options/Black Scholes.ipynb` — Black-Scholes Pricing from Scratch
Derives and implements the Black-Scholes formula for European call and put options, verifies Put-Call Parity, and analyses how each input parameter drives option price.

**The formula:** `C = S·N(d₁) − K·e^(−rT)·N(d₂)`

**What's covered:**
- Implementing `calculateD1`, `calculateD2`, `calculateCallOptionPrice`, and `calculatePutOptionPrice` from the raw BS formula
- Pricing ATM options: C ≈ 10.45, P ≈ 5.57 (S=K=100, σ=20%, r=5%, T=1yr)
- **Put-Call Parity** verification: `C − P = S − K·e^(−rT)` confirmed to machine precision
- **4-panel sensitivity analysis** — call price vs σ, T, S, and r (others held fixed)

**Key findings:**
- Call price increases monotonically with σ, T (when S > K), and r
- Call price is most sensitive to underlying price when near the strike — this is where Delta is highest
- The `.py` module (`Black_Scholes.py`) is imported by `Greeks.ipynb` for reuse

---

### 8. `Options/Greeks.ipynb` — Delta, Gamma, Vega, Theta
Implements all four first-order Greeks analytically using the Black-Scholes framework and visualises their behaviour across a range of stock prices.

**What's covered:**
- **Delta** `N(d₁)` — sensitivity of option price to underlying price; S-curve from 0 (deep OTM) to 1 (deep ITM)
- **Gamma** `N'(d₁) / (S·σ·√T)` — rate of change of Delta; peaks sharply at-the-money
- **Vega** `S·N'(d₁)·√T` — sensitivity to volatility; also peaks ATM
- **Theta** — time decay for call and put; separate plot showing **theta acceleration** as expiry approaches (3-month and 1-month markers)
- All four Greeks plotted in a **2×2 grid** across stock prices 1–200 (K = 100)

**Key insights:**
- Delta ≈ 0.637 for ATM call (S=K=100), confirming ≈50% ITM probability adjusted for drift
- Gamma and Vega are highest ATM — this is where the option is most sensitive to small moves and vol changes
- Theta decay is non-linear and accelerates sharply inside the final month — critical for short-options strategies

---

## Stack

| Library | Purpose |
|---|---|
| `yfinance` | Live market data download |
| `pandas` | Data wrangling and return calculations |
| `numpy` | Matrix operations, Brownian motion simulation |
| `scipy.stats` | Descriptive stats, distribution fitting, t-tests, norm CDF/PDF |
| `matplotlib` | All plots — histograms, sensitivity charts, Greek curves |
| `seaborn` | Correlation / covariance heatmaps, loadings heatmap |
| `sklearn` | StandardScaler, PCA |
| `math` | Scalar BS calculations (log, exp, sqrt) |

---

## Getting Started

```bash
git clone https://github.com/kanak27/Quant-journey.git
cd Quant-journey
pip install pandas yfinance matplotlib seaborn scipy scikit-learn jupyter
jupyter notebook
```

Notebooks in `Options/` that import `.py` modules (e.g. `Greeks.ipynb` imports `Black_Scholes.py`) must be run from within the `Options/` directory, or the kernel's working directory set to `Options/`.

All market data notebooks fetch live data on execution, so results update automatically with the latest prices.

---

## Roadmap

This repo tracks a structured 7-month plan (April → November 2026) toward quant finance roles at firms like WorldQuant, Tower Research, iRage, and Citadel.

### ✅ Phase 1 — Mathematical & Programming Foundation *(May 2026 — complete)*

- [x] Python finance stack: NumPy, Pandas, Matplotlib, Seaborn, SciPy, yfinance
- [x] Return distributions — daily % returns, log returns, CDFs, normal fitting
- [x] Descriptive statistics — mean, variance, skewness, kurtosis
- [x] Covariance & correlation matrices on a 5-stock Nifty basket
- [x] OLS regression from scratch + hypothesis testing (t-test, p-values)
- [x] PCA for dimensionality reduction and latent factor discovery

### 🔄 Phase 2 — Quantitative Finance Core *(May 26 – July 6, 2026 — in progress)*

- [x] Geometric Brownian Motion — simulation engine (100 / 1K / 10K paths)
- [x] Options basic payoffs — Long/Short Call & Put, Covered Call
- [x] Black-Scholes from scratch — call & put pricing, Put-Call Parity verified
- [x] Greeks — Delta, Gamma, Vega, Theta (analytical + 2×2 visualisation, theta decay curve)
- [ ] Monte Carlo options pricing (connect GBM paths to BS pricing)
- [ ] GARCH(1,1) — fit to Nifty 50 volatility
- [ ] Time series — autocorrelation, stationarity (ADF test), ARIMA
- [ ] C++ — Black-Scholes pricer (first C++ finance implementation)

### ⬜ Phase 3 — Machine Learning for Finance *(July 7 – August 16, 2026)*

- [ ] CAPM — alpha, beta, systematic vs idiosyncratic risk
- [ ] Fama-French 3-Factor Model on NSE data
- [ ] Momentum factor (Jegadeesh-Titman)
- [ ] ML for return prediction — Random Forest, XGBoost
- [ ] Walk-forward cross-validation (avoid look-ahead bias)
- [ ] Backtesting a momentum strategy on QuantConnect

### ⬜ Phase 4 — Portfolio Projects *(August 17 – September 27, 2026)*

- [ ] **Portfolio Manager** — Markowitz optimisation, efficient frontier, VaR/CVaR, live Zerodha data, Streamlit dashboard
- [ ] **Pairs Trading** — cointegration (Engle-Granger), Kalman filter hedge ratio, QuantConnect backtest
- [ ] **Options Analytics Dashboard** — BS + Binomial pricing, Greeks surface plots, volatility smile
- [ ] **Market Regime Detection** — Hidden Markov Model on Nifty 50, regime-conditioned strategy switching

### ⬜ Phase 5 — Interview Preparation *(September 28 – November 15, 2026)*

- [ ] Probability & brain teasers — 2 problems/day (Mosteller, Green Book)
- [ ] LeetCode — 3 medium + 1 hard per day in Python & C++
- [ ] Derive Black-Scholes on a whiteboard from memory
- [ ] Mock interviews (Pramp, Interviewing.io)
- [ ] 20+ applications — WorldQuant, Tower, iRage, AlphaGrep, Graviton, Quadeye

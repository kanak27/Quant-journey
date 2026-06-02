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
└── Options/                          # Options theory — see Options/README.md
    ├── Options basic payoffs.ipynb
    ├── Geometric Brownian Motion.ipynb
    ├── Black Scholes.ipynb
    ├── Greeks.ipynb
    ├── Monte Carlo Options Pricing.ipynb
    ├── Black_Scholes.py
    ├── Geometric_Brownian_Motion.py
    └── Options_basic_payoffs.py
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

### 5. `Options/` — Options Theory & Pricing
Five notebooks covering options from first principles through to exotic contract pricing. Each notebook builds on the last and shares reusable `.py` modules.

| Notebook | Topic |
|---|---|
| `Options basic payoffs.ipynb` | Long/Short Call & Put, Covered Call |
| `Geometric Brownian Motion.ipynb` | Monte Carlo stock price simulation |
| `Black Scholes.ipynb` | BS pricing, Put-Call Parity, sensitivity analysis |
| `Greeks.ipynb` | Delta, Gamma, Vega, Theta — analytical + visualised |
| `Monte Carlo Options Pricing.ipynb` | MC pricing of European & Asian options, convergence to BS |

→ Full details in [Options/README.md](Options/README.md)

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

Notebooks inside `Options/` import local `.py` modules — run Jupyter from within the `Options/` directory, or set the kernel working directory to `Options/` before executing.

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
- [x] Greeks — Delta, Gamma, Vega, Theta (analytical + visualised, theta decay curve)
- [x] Monte Carlo options pricing — European & Asian options, convergence to BS
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

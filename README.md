# Quant Journey 📈

A personal learning repository documenting my path into quantitative finance. Each notebook explores a core concept in financial data analysis and statistical modelling, applied to real Indian market data pulled live from Yahoo Finance.

---

## Repository Structure

```
Quant Journey/
├── Nifty50 Quant prep.ipynb              # Return distributions & descriptive stats
├── Covariance and Correlation.ipynb      # Portfolio diversification analysis
├── OLS.ipynb                             # OLS regression & hypothesis testing
├── PCA.ipynb                             # Principal component analysis
├── Time Series and Volatility/          # Stationarity, autocorrelation, ARIMA, GARCH
│   ├── ADF.ipynb                        # Stationarity testing — ADF test
│   ├── ACF and PACF.ipynb               # Autocorrelation & partial autocorrelation
│   ├── ARIMA.ipynb                      # ARIMA model identification & fitting
│   └── ARCH and GARCH.ipynb             # GARCH(1,1) volatility modelling
└── Options/                             # Options theory — see Options/README.md
    ├── Options basic payoffs.ipynb
    ├── Geometric Brownian Motion.ipynb
    ├── Black Scholes.ipynb
    ├── Greeks.ipynb
    ├── Monte Carlo Options Pricing.ipynb
    ├── Black_Scholes.cpp                 # C++ OOP implementation
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

### 5. `Time Series and Volatility/` — Stationarity, Autocorrelation, ARIMA & GARCH
Four notebooks that form the classical time-series toolkit: first establish what is and isn't stationary, then look for linear structure in the mean, then model the structure that *is* reliably there — the volatility. They build on each other and are best read in order.

| File | Topic |
|---|---|
| `ADF.ipynb` | Augmented Dickey-Fuller unit-root / stationarity test |
| `ACF and PACF.ipynb` | Autocorrelation & partial autocorrelation of returns |
| `ARIMA.ipynb` | ARIMA order identification & fitting on returns |
| `ARCH and GARCH.ipynb` | GARCH(1,1) conditional-volatility model |

#### 5a. `ADF.ipynb` — Stationarity Testing (Augmented Dickey-Fuller)
Tests whether the Nifty 50 price series and its return series are stationary — the prerequisite for everything that follows.

**What's covered:**
- Running `statsmodels.tsa.stattools.adfuller` on both the **raw price series** and the **daily return series**
- Comparing the ADF statistic against 1%, 5%, and 10% critical values and reading the p-value

**Key findings:**
- Closing prices: ADF ≈ −1.53, p ≈ 0.52 → **non-stationary** (fail to reject the unit-root null)
- Daily returns: ADF ≈ −5.31, p ≈ 5.2e-06 → **stationary** (strongly reject the unit root)
- Confirms that returns, not prices, are the right input to ARMA/GARCH-type models

#### 5b. `ACF and PACF.ipynb` — Autocorrelation Structure
Inspects the linear memory of the return series to guide ARIMA order selection.

**What's covered:**
- `plot_acf` and `plot_pacf` on daily returns (30 lags) with 95% confidence bands

**Key findings:**
- Almost all autocorrelation and partial-autocorrelation spikes fall **inside** the confidence bands → the return series behaves close to **white noise** in the mean
- This immediately tells us to expect very low AR/MA orders — there is little linear structure to fit

#### 5c. `ARIMA.ipynb` — ARIMA Identification & Fitting
Fits a range of ARIMA(p, d, q) specifications to the return series and compares them by information criteria and residual diagnostics.

**What's covered:**
- Fitting `(1,0,1)`, `(1,0,0)`, `(0,0,1)`, `(1,1,1)`, `(0,0,0)` and reading AIC/BIC + the Ljung-Box residual test from `model_fit.summary()`

**Key findings:**
- The plain mean model **ARIMA(0,0,0)** (AIC ≈ 607) is essentially as good as anything more complex; Ljung-Box is non-significant across specs → no exploitable autocorrelation
- The `(1,0,1)` fit has a marginally lower AIC but its AR and MA roots nearly cancel (ar ≈ −0.97, ma ≈ +0.92), a textbook sign of an over-parameterised, redundant model
- Bottom line: **daily returns are unpredictable in the mean** — the same weak-form-EMH conclusion the OLS notebook reached, now confirmed by the full ARIMA family

#### 5d. `ARCH and GARCH.ipynb` — Volatility Clustering
Where the mean has no structure, the *variance* clearly does. Fits a GARCH(1,1) to seven years of Nifty log returns and compares its conditional volatility to a naïve rolling-window estimate.

**What's covered:**
- Seven years of ^NSEI data, log returns scaled to percent for the `arch` optimiser
- Fitting `arch.arch_model(returns, vol='Garch', p=1, q=1)` and reading the ω / α / β estimates
- Overlaying the **GARCH conditional volatility** against a **30-day rolling standard deviation**

**Key findings:**
- ω ≈ 0.028, α ≈ 0.12, β ≈ 0.855 → **α + β ≈ 0.98**, i.e. very high volatility persistence: shocks to volatility decay slowly and vol clusters strongly
- GARCH conditional vol tracks the rolling estimate but reacts **faster** to shocks and is far smoother between them — the payoff of an explicit volatility model
- A small but statistically significant positive mean return (μ ≈ 0.066% / day) survives, unlike in the ARIMA mean models

---

### 6. `Options/` — Options Theory & Pricing
Five notebooks covering options from first principles through to exotic contract pricing. Each notebook builds on the last and shares reusable `.py` modules.

| File | Topic |
|---|---|
| `Options basic payoffs.ipynb` | Long/Short Call & Put, Covered Call |
| `Geometric Brownian Motion.ipynb` | Monte Carlo stock price simulation |
| `Black Scholes.ipynb` | BS pricing, Put-Call Parity, sensitivity analysis |
| `Greeks.ipynb` | Delta, Gamma, Vega, Theta — analytical + visualised |
| `Monte Carlo Options Pricing.ipynb` | MC pricing of European & Asian options, convergence to BS |
| `Black_Scholes.cpp` | C++ OOP pricer — `Option` class with price, Greeks |

→ Full details in [Options/README.md](Options/README.md)

---

## Stack

| Library | Purpose |
|---|---|
| `yfinance` | Live market data download |
| `pandas` | Data wrangling and return calculations |
| `numpy` | Matrix operations, Brownian motion simulation |
| `scipy.stats` | Descriptive stats, distribution fitting, t-tests, norm CDF/PDF |
| `matplotlib` | All plots — histograms, sensitivity charts, Greek curves, volatility overlays |
| `seaborn` | Correlation / covariance heatmaps, loadings heatmap |
| `sklearn` | StandardScaler, PCA |
| `statsmodels` | ADF stationarity test, ACF/PACF, ARIMA |
| `arch` | GARCH(1,1) conditional-volatility modelling |
| `math` | Scalar BS calculations (log, exp, sqrt) |
| C++ (`<cmath>`, `<iostream>`) | Low-latency BS pricer — `Option` OOP class |

---

## Getting Started

```bash
git clone https://github.com/kanak27/Quant-journey.git
cd Quant-journey
pip install pandas yfinance matplotlib seaborn scipy scikit-learn statsmodels arch jupyter
jupyter notebook
```

Notebooks inside `Options/` import local `.py` modules — run Jupyter from within the `Options/` directory, or set the kernel working directory to `Options/` before executing. The `Time Series and Volatility/` notebooks are self-contained (they download their own data) and can be run from anywhere.

> **Note on reproducibility:** every notebook downloads a *live* rolling window from Yahoo Finance, so the exact figures above shift a little each time the notebooks are re-run — the ADF, ACF and ARIMA notebooks use a 1-year window, while the GARCH notebook uses 7 years. The qualitative conclusions are stable; the third-decimal-place numbers are not.

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
- [x] Stationarity testing — ADF test on Nifty 50 prices vs returns
- [x] Autocorrelation — ACF & PACF of the return series
- [x] Time series — ARIMA model identification & fitting
- [x] GARCH(1,1) — fit to Nifty 50 volatility, vs 30-day rolling vol
- [x] C++ — Black-Scholes pricer — `Option` class with `price()`, `putPrice()`, `delta()`, `gamma()`, `vega()`

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
```


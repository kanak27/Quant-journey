# Quant Journey 📈

A personal learning repository documenting my path into quantitative finance. Each notebook explores a core concept in financial data analysis and statistical modelling, applied to real Indian market data pulled live from Yahoo Finance.

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

### 2. `Covariance and Corelation.ipynb` — Portfolio Diversification Analysis
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

### 5. `Geometric Brownian Motion.ipynb` — Monte Carlo Stock Price Simulation
Implements the GBM stochastic process from scratch to simulate realistic stock price paths, forming the backbone of options pricing models.

**The model:** `S(t) = S₀ · exp((μ − 0.5σ²)t + σW(t))`

**What's covered:**
- Deriving the discrete GBM formula and implementing `simulate_gbm()` using cumulative Brownian increments
- Building a **simulation engine** that runs an arbitrary number of independent paths (100 / 1 000 / 10 000 runs)
- Plotting all simulated price paths and the resulting **terminal price histogram**
- Observing convergence: as simulation runs increase the terminal price distribution converges toward a log-normal

**Parameters used:** S₀ = 100, μ = 5%, σ = 20%, T = 1 year, N = 252 trading days

**Key insight:** The right-skewed terminal price distribution reflects the log-normal assumption embedded in GBM — the same assumption underpinning Black–Scholes.

---

### 6. `Options basic payoffs.ipynb` — Options Payoff Diagrams & Covered Call
Builds intuition for vanilla options by computing and plotting payoff profiles for all four basic positions, then constructs a Covered Call strategy.

**What's covered:**
- Implementing payoff functions for **Long Call**, **Long Put**, **Short Call**, and **Short Put** (profit = payoff − premium)
- Generating a payoff table across stock prices 1–100 (K = 50, premium = 10)
- Plotting all four payoffs as a 2×2 subplot grid
- Combining a **long stock position** with a **short call** to produce a **Covered Call** payoff and plotting the capped-upside profile

**Key insight:** The Covered Call caps profit at `premium + (K − cost_of_stock)` = 20, while retaining full downside exposure — illustrating the classic income-vs-protection trade-off.

---

## Stack

| Library | Purpose |
|---|---|
| `yfinance` | Live market data download |
| `pandas` | Data wrangling and return calculations |
| `numpy` | Matrix operations (OLS normal equations) |
| `scipy.stats` | Descriptive stats, distribution fitting, t-tests, linregress |
| `matplotlib` | Histograms, CDF plots, scree plots, biplots |
| `seaborn` | Correlation / covariance heatmaps, loadings heatmap |
| `sklearn` | StandardScaler, PCA |

---

## Getting Started

```bash
git clone https://github.com/kanak27/Quant-journey.git
cd Quant-journey
pip install pandas yfinance matplotlib seaborn scipy scikit-learn jupyter
jupyter notebook
```

All notebooks fetch live data on execution, so results will update automatically with the latest market prices.

---

## Roadmap

- [ ] Value at Risk (VaR) and Expected Shortfall
- [ ] Markowitz mean-variance portfolio optimisation
- [ ] Factor models (Fama–French)
- [ ] Time series — ARIMA / GARCH on index returns
- [x] GBM simulation (Monte Carlo paths)
- [x] Options basic payoffs & Covered Call
- [ ] Options pricing (Black–Scholes)

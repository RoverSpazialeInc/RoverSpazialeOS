#ifndef INC_WCET_ESTIMATION_DWT_H_
#define INC_WCET_ESTIMATION_DWT_H_

#include <stdint.h>
#include "stm32g4xx.h"        // Registri Core (DWT, CoreDebug, IRQn_Type, ecc.)
#include "stm32g4xx_hal.h"    // HAL_RCC_GetHCLKFreq()

/*
 * ============================================================================
 *  DWT – Data Watchpoint and Trace
 * ============================================================================
 *
 * Questo modulo usa il contatore di cicli del core ARM Cortex-M (DWT->CYCCNT)
 * per misurare il tempo di esecuzione del codice in termini di cicli di clock.
 *
 * Vantaggi:
 *  - Precisione a singolo ciclo
 *  - Overhead minimo
 *  - Ideale per WCET estimation e profiling
 *
 * Requisiti:
 *  - Core Cortex-M con DWT (es. M4)
 *  - DWT_Init() va chiamata UNA SOLA VOLTA all’avvio
 */

/* ---------------------------------------------------------------------------
 * Inizializza il contatore di cicli DWT
 * ---------------------------------------------------------------------------
 * - Abilita il tracing nel CoreDebug
 * - Azzera il contatore di cicli
 * - Abilita il cycle counter
 */
void DWT_Init(void);

/* ---------------------------------------------------------------------------
 * Avvia una misura di tempo
 * ---------------------------------------------------------------------------
 * Ritorna il valore corrente del contatore di cicli.
 * Il valore va poi passato a DWT_End().
 *
 * Le istruzioni DSB/ISB assicurano che:
 *  - tutte le istruzioni precedenti siano completate
 *  - la pipeline sia sincronizzata
 * così la misura è più accurata.
 */
static inline uint32_t DWT_Begin(void)
{
    __DSB();   // Data Synchronization Barrier
    __ISB();   // Instruction Synchronization Barrier
    return DWT->CYCCNT;
}

/* ---------------------------------------------------------------------------
 * Termina una misura di tempo
 * ---------------------------------------------------------------------------
 * start : valore restituito da DWT_Begin()
 *
 * Ritorna il numero di cicli trascorsi.
 * La sottrazione è corretta anche in caso di overflow (uint32).
 */
static inline uint32_t DWT_End(uint32_t start)
{
    __DSB();
    __ISB();
    return (uint32_t)(DWT->CYCCNT - start);
}

/* ---------------------------------------------------------------------------
 * Converte cicli CPU in microsecondi
 * ---------------------------------------------------------------------------
 * Usa la frequenza HCLK corrente (HAL_RCC_GetHCLKFreq()).
 * Calcolo fatto in aritmetica intera (no float) con rounding.
 */
uint32_t DWT_CyclesToUs_u32(uint32_t cycles);

/* ---------------------------------------------------------------------------
 * Stampa il risultato della misura
 * ---------------------------------------------------------------------------
 * Stampa:
 *   <tag> Cy=<cicli> (<microsecondi> us)
 *
 * Usa le funzioni definite in print.h
 */
void DWT_PrintCyclesAndUs(const char *tag, uint32_t cycles);

/* ---------------------------------------------------------------------------
 * Busy-wait delay in microseconds
 * ---------------------------------------------------------------------------
 * Richiede DWT_Init() chiamata all'avvio.
 */
void DWT_DelayUs(uint32_t us);

/*
 * ---------------------------------------------------------------------------
 * Esempio di utilizzo
 * ---------------------------------------------------------------------------
 *
 * uint32_t t0 = DWT_Begin();
 * // codice da misurare
 * uint32_t cycles = DWT_End(t0);
 *
 * DWT_PrintCyclesAndUs("CTRL", cycles);
 */

#endif /* INC_WCET_ESTIMATION_DWT_H_ */

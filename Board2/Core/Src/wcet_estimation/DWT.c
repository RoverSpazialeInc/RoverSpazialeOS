#include "DWT.h"
#include "print.h"

/*
 * ---------------------------------------------------------------------------
 * DWT_Init
 * ---------------------------------------------------------------------------
 * Abilita il contatore di cicli del core Cortex-M.
 *
 * Passi:
 * 1. Abilita il tracing (TRCENA) nel CoreDebug
 * 2. Azzera il contatore di cicli
 * 3. Abilita il cycle counter nel DWT
 *
 * Questa funzione va chiamata una sola volta all'avvio del sistema.
 */
void DWT_Init(void)
{
    /* Abilita accesso a DWT e ITM */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    /* Reset del contatore di cicli */
    DWT->CYCCNT = 0;

    /* Abilita il contatore di cicli */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/*
 * ---------------------------------------------------------------------------
 * DWT_CyclesToUs_u32
 * ---------------------------------------------------------------------------
 * Converte un numero di cicli CPU in microsecondi.
 *
 * Formula:
 *   us = cycles * 1e6 / f_cpu
 *
 * - f_cpu è la frequenza HCLK in Hz
 * - usa uint64_t per evitare overflow
 * - aggiunge f_cpu/2 per arrotondamento corretto
 */
uint32_t DWT_CyclesToUs_u32(uint32_t cycles)
{
    uint32_t f_cpu = HAL_RCC_GetHCLKFreq(); // Frequenza CPU (Hz)

    uint64_t num = (uint64_t)cycles * 1000000ULL + (f_cpu / 2U);
    return (uint32_t)(num / (uint64_t)f_cpu);
}

/*
 * ---------------------------------------------------------------------------
 * DWT_PrintCyclesAndUs
 * ---------------------------------------------------------------------------
 * Stampa il numero di cicli misurati e il tempo equivalente in microsecondi.
 *
 * Formato di output:
 *   <tag> Cy=<cicli> (<microsecondi> us)
 *
 * Se tag è NULL o stringa vuota, viene omesso.
 */
void DWT_PrintCyclesAndUs(const char *tag, uint32_t cycles)
{
    uint32_t us = DWT_CyclesToUs_u32(cycles);

    if (tag && tag[0] != '\0')
    {
        printLabel(tag);
        printMsg(" ");
    }

    printMsg("Cy=");
    printInt((int32_t)cycles);
    printMsg(" (");
    printInt((int32_t)us);
    printMsg(" us)");
    printNewLine();
}

void DWT_DelayUs(uint32_t us)
{
    if (us == 0u) {
        return;
    }

    const uint32_t f_cpu = HAL_RCC_GetHCLKFreq();
    const uint32_t cycles_per_us = f_cpu / 1000000u;

    /* Se f_cpu < 1MHz, non ha senso fare delay preciso in us */
    if (cycles_per_us == 0u) {
        return;
    }

    /* Chunking per evitare overflow nei cicli */
    const uint32_t max_cycles = 0x7FFFFFFFu;
    const uint32_t max_us_chunk = max_cycles / cycles_per_us;

    while (us > 0u) {
        uint32_t chunk_us = us;
        if (chunk_us > max_us_chunk) {
            chunk_us = max_us_chunk;
        }

        const uint32_t start = DWT->CYCCNT;
        const uint32_t target_cycles = chunk_us * cycles_per_us;

        while ((uint32_t)(DWT->CYCCNT - start) < target_cycles) {
            __NOP();
        }

        us -= chunk_us;
    }
}

#ifndef _PRIVATE_TIMER_H_
#define _PRIVATE_TIMER_H_

#include <stdint.h>

typedef struct
{
    volatile uint32_t LOAD;
    volatile uint32_t COUNTER;
    volatile uint32_t CONTROL;
    volatile uint32_t ISR;
} ptimer_reg_t;

/* Values for control register */
#define PRIVATE_TIMER_CONTROL_PRESCALER_MASK    0x0000FF00
#define PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT    8
#define PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK    0x00000004
#define PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK    0x00000002
#define PRIVATE_TIMER_CONTROL_ENABLE_MASK        0x00000001

/* Values for ISR register */
#define PRIVATE_TIMER_ISR_EVENT_FLAG_MASK        0x00000001


#define PRIVATE_TIMER_BASE            0xF8F00600
#define PRIVATE_TIMER                ((ptimer_reg_t*)PRIVATE_TIMER_BASE)

static inline void PrivateTimerStart(ptimer_reg_t* timer)
{
    timer->CONTROL |= PRIVATE_TIMER_CONTROL_ENABLE_MASK;
}

static inline void PrivateTimerStop(ptimer_reg_t* timer)
{
    timer->CONTROL &= ~PRIVATE_TIMER_CONTROL_ENABLE_MASK;
}

static inline void PrivateTimerLoad(ptimer_reg_t* timer, uint32_t value)
{
    timer->COUNTER = value;
}

static inline uint32_t PrivateTimerGetCounterValue(ptimer_reg_t* timer)
{
    return timer->COUNTER;
}

static inline void PrivateTimerEnableAutoReload(ptimer_reg_t* timer, uint32_t reloadValue)
{
    timer->LOAD = reloadValue;
    timer->CONTROL |= PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;
}

static inline void PrivateTimerDisableAutoReload(ptimer_reg_t* timer)
{
    timer->CONTROL &= ~PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;
}

static inline void PrivateTimerEnableInterrupt(ptimer_reg_t* timer)
{
    timer->CONTROL |= PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK;
}

static inline void PrivateTimerDisableInterrupt(ptimer_reg_t* timer)
{
    timer->CONTROL &= ~PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK;
}

static inline void PrivateTimerSetPrescaler(ptimer_reg_t* timer, uint8_t prescaler)
{
    uint32_t ctrl = timer->CONTROL;
    ctrl &= ~PRIVATE_TIMER_CONTROL_PRESCALER_MASK;
    ctrl |= (prescaler << PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT);
    timer->CONTROL = ctrl;
}

static inline uint8_t PrivateTimerGetPrescaler(ptimer_reg_t* timer)
{
    return (timer->CONTROL & PRIVATE_TIMER_CONTROL_PRESCALER_MASK) >> PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT;
}

static inline uint32_t PrivateTimerIsExpired(ptimer_reg_t* timer)
{
    return (timer->ISR & PRIVATE_TIMER_ISR_EVENT_FLAG_MASK) == PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;
}

static inline void PrivateTimerClearExpiration(ptimer_reg_t* timer)
{
    timer->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;
}

#endif


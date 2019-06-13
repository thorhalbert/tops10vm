
/*APR CONI BITS: */

#define AP_POV	BIT19		/* PUSH DOWN OVERFLOW */
#define AP_UIO	BIT20		/* USER IN-OUT */
#define AP_ABK	BIT21		/* ADDRESS BREAK */
#define AP_ILM	BIT22		/* ILLEGAL MEMORY */
#define AP_NXM	BIT23		/* NON-EXIST. MEMORY */
#define UE_PEF	BIT24		/* PARITY ENABLE (AND INTERRUPT) */
                                /* MONITOR MAKES PARITY BIT APPEAR HERE */
#define AP_CIE	BIT25		/* CLOCK INTERRUPT ENABLED */
#define AP_CLK	BIT26		/* CLOCK (HAS INTERRUPTED) */
#define AP_PPV	BIT27		/* FLAG FOR PROPRITARY PAGE VIOLATION */
                                /* A CONI BIT.  USED FOR IMPROVED ERROR */
#define AP_FOE	BIT28		/* FLOATING OVERFLOW ENABLED */
#define AP_FOV	BIT29		/* FLOATING OVERFLOW (HAS INTERRUPTED) */
#define AP_TOS	BIT30		/* TRAP OFF SET - MASTER VS_ SLAVE */
#define AP_AOE	BIT31		/* ARITHMETIC OVERFLOW ENABLED */
#define AP_AOV	BIT32		/* ARITHMETIC OVERFLOW */

/* APR CONO BITS: */
/* (DIFFERENT NAMES FROM CONI ONLY BECAUSE SOME HAVE DIFFERENT FUNCTIONS) */

#define AP_CPO	BIT18		/* CLEAR PDL OVF */
#define AP_DDU	BIT18		/* DON'T DISABLE USER ENABLED INTERRUPTS */
                                /* when THEY OCCUR. SOFTWARE BIT, NOT HARD */
#define AP_IOR	BIT19		/* IO RESET (CLEAR ALL DEVICES) */
#define AP_CAB	BIT21		/* CLEAR ADDRESS BREAK */
#define AP_CMP	BIT22		/* CLEAR MEMORY PROTECTION */
#define AP_CNM	BIT23		/* CLEAR NON-EXISTENT MEMORY */
#define AP_DCI	BIT24		/* DISABLE CLOCK INTERRUPT */
#define AP_ECI	BIT25		/* ENABLE CLOCK INTERRUPT */
#define AP_CCF	BIT26		/* CLEAR CLOCK FLAG */
#define AP_DFO	BIT27		/* DISABLE FLOAT_ OVERFLOW */
#define AP_EFO	BIT28		/* ENABLE FLOAT. OVERFLOW */
#define AP_CFO	BIT29		/* CLEAR FLOATING OVERFLOW */
#define AP_DAO	BIT30		/* DISABLE ARITH. OVERFLOW */
#define AP_EAO	BIT31		/* ENABLE ARITH. OVERFLOW */
#define AP_CAO	BIT32		/* CLEAR ARITH. OVERFLOW */
#define AP_PI0	7B35		/* PI CHANNEL FOR CPU 0 */
#define AP_PI1	7B35		/* PI CHANNEL FOR CPU 1 */

/* APR DATAO BITS: */

#define AP_UWP	BIT17		/* USER MODE WRITE PROTECT FOR HIGH SEGMENT */

/* PC FLAGS */

#define PC_OVF	BIT0		/* OVERFLOW */
#define PC_CY0	BIT1		/* CARRY 0 */
#define PC_CY1	BIT2		/* CARRY 1 */
#define PC_FOV	BIT3		/* FLOATING OVER FLOW */
#define PC_BIS	BIT4		/* BYTE INCREMENT SUPPRESSION */
#define PC_USR	BIT5		/* USER MODE */
#define PC_UIO	BIT6		/* USER IO MODE */
#define PC_FUF	BIT11		/* FLOATING UNDER FLOW */
#define PC_NDV	BIT12		/* NO DIVIDE */

/* PI CONI BITS: */

#define PI_PWF	BIT18		/* POWER FAILURE */
#define PI_PAR	BIT19		/* PARITY ERROR IN MEMORY */
#define PI_PEE	BIT20		/* PARITY ERROR ENABLED */
#define PI_IP1	BIT21		/* INTERRUPT IN PROGRESS ON CHANNEL 1 */
#define PI_IP2	BIT22		/*      "           "               2 */
#define PI_IP3	BIT23		/*      "           "               3 */
#define PI_IP4	BIT24		/*      "           "               4 */
#define PI_IP5	BIT25		/*      "           "               5 */
#define PI_IP6	BIT26		/*      "           "               6 */
#define PI_IP7	BIT27		/*      "           "               7 */
#define PI_IPA	(PI_IP1|PI_IP2|PI_IP3|PI_IP4|PI_IP5|PI_IP6|PI_IP7)
                                /* INTERRUPTING PROG ON ALL */
#define PI_PIA	BIT28		/* PI ACTIVE */
#define PI_CO1	BIT29		/* CHANNEL ON 1 */
#define PI_CO2	BIT30		/*     "    " 2 */
#define PI_CO3	BIT31		/*     "    " 3 */
#define PI_CO4	BIT32		/*     "    " 4 */
#define PI_CO5	BIT33		/*     "    " 5 */
#define PI_CO6	BIT34		/*     "    " 6 */
#define PI_CO7	BIT35		/*     "    " 7 */

/* PI CONO BITS: */
/* (DIFFERENT NAMES FROM CONI ONLY BECAUSE SOME HAVE DIFF FUNCTIONS) */

#define PI_CPF	BIT18		/* CLEAR POWER FAILURE */
#define PI_CPE	BIT19		/* CLEAR PARITY ERROR */
#define PI_DPE	BIT20		/* DISABLE PARITY ERROR */
#define PI_EPE	BIT21		/* ENABLE PARITY ERROR */
#define PI_CPI	BIT23		/* CLEAR PI SYSTEM */
#define PI_IIO	BIT24		/* INITIATE INTERRUPT ON (SELECTED PIS) */
#define PI_TNP	BIT25		/* TURN ON SELECTED PIS */
#define PI_TFP	BIT26		/* TURN OFF SELECTED PIS */
#define PI_OFF	BIT27		/* TURN PI SYSTEM OFF */
#define PI_ON	BIT28		/* TURN PI SYSTEM ON */
#define PI_SC1	BIT29		/* SELECT CHANNELS 1 */
#define PI_SC2	BIT30		/*    "       "    2 */
#define PI_SC3	BIT31		/*    "       "    3 */
#define PI_SC4	BIT32		/*    "       "    4 */
#define PI_SC5	BIT33		/*    "       "    5 */
#define PI_SC6	BIT34		/*    "       "    6 */
#define PI_SC7	BIT35		/*    "       "    7 */

/* CPU TYPE CODES (RH OF .CPTYP)(LH FOR CUSTOMERS) */

#define CT_P6	1		/* PDP-6 TYPE PROCESSOR */
#define CT_KA	2		/* KA-10 TYPE PROCESSOR */
#define CT_KI	3		/* KI-10 TYPE PROCESSOR */
#define CT_KL	4		/* KL-10 TYPE PROCESSOR */
#define CT_KS	5		/* KS-10 TYPE PROCESSOR */

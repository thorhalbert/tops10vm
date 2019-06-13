#define	CALLI_LIGHTS	0777777	// X
#define	CALLI_RESET	00	// 
#define	CALLI_DDTIN	01	// A B
#define	CALLI_SETDDT	02	// X
#define	CALLI_DDTOUT	03	// A B
#define	CALLI_DEVCHR	04	// CDU
#define	CALLI_DDTGT	05	// ?
#define	CALLI_GETCHR	06	// CDU
#define	CALLI_DDTRL	07	// ?
#define	CALLI_WAIT	010	// I
#define	CALLI_CORE	011	// X,,X S
#define	CALLI_EXIT	012	// IQ
#define	CALLI_UTPCLR	013	// CU
#define	CALLI_DATE	014	// R
#define	CALLI_LOGIN	015	// -L,,A
#define	CALLI_APRENB	016	// Q
#define	CALLI_LOGOUT	017	// IQ
#define	CALLI_SWITCH	020	// R
#define	CALLI_REASSI	021	// J\CDU
#define	CALLI_TIMER	022	// R
#define	CALLI_MSTIME	023	// R
#define	CALLI_GETPPN	024	// RS
#define	CALLI_TRPSET	025	// L,,A
#define	CALLI_TRPJEN	026	//
#define	CALLI_RUNTIM	027	// 0J
#define	CALLI_PJOB	030	// R
#define	CALLI_SLEEP	031	// X
#define	CALLI_SETPOV	032	// ?
#define	CALLI_PEEK	033	// A
#define	CALLI_GETLIN	034	// R
#define	CALLI_RUN	035	// X,,A S
#define	CALLI_SETUWP	036	// QS
#define	CALLI_REMAP	037	// X,,X
#define	CALLI_GETSEG	040	// AS
#define	CALLI_GETTAB	041	// X,,X J,,X S
#define	CALLI_SPY	042	// X
#define	CALLI_SETNAM	043	// X last in 3.19, 4.50
#define	CALLI_TMPCOR	044	// F,,A S
#define	CALLI_DSKCHR	045	// L,,A S last in 4.72
#define	CALLI_SYSSTR	046	// D X S
#define	CALLI_JOBSTR	047	// L,,A S
#define	CALLI_STRUUO	050	// L,,A S
#define	CALLI_SYSPHY	051	// 0 D S
#define	CALLI_FRECHN	052	// ?
#define	CALLI_DEVTYP	053	// CDU S
#define	CALLI_DEVSTS	054	// CDU S
#define	CALLI_DEVPPN	055	// CD S
#define	CALLI_SEEK	056	// IC last in 5.01
#define	CALLI_RTTRP	057	// A S
#define	CALLI_LOCK	060	// X,,X -L,,A S
#define	CALLI_JOBSTS	061	// C -J U S
#define	CALLI_LOCATE	062	// X
#define	CALLI_WHERE	063	// CDU S
#define	CALLI_DEVNAM	064	// CDU S
#define	CALLI_CTLJOB	065	// J S
#define	CALLI_GOBSTR	066	// L,,A S last in 5.02
#define	CALLI_ACTIVA	067	// ?
#define	CALLI_DEACTI	070	// ?
#define	CALLI_HPQ	071	// X S
#define	CALLI_HIBER	072	// Q,,X S
#define	CALLI_WAKE	073	// J S
#define	CALLI_CHGPPN	074	// X S
#define	CALLI_SETUUO	075	// F,,A S
#define	CALLI_DEVGEN	076	// ? (CODE EXISTS)
#define	CALLI_OTHUSR	077	// S
#define	CALLI_CHKACC	0100	// A S
#define	CALLI_DEVSIZ	0101	// A S
#define	CALLI_DAEMON	0102	// L,,A S
#define	CALLI_JOBPEK	0103	// X S
#define	CALLI_ATTACH	0104	// X,,J S
#define	CALLI_DAEFIN	0105	// L,,A S
#define	CALLI_FRCUUO	0106	// L,,A S
#define	CALLI_DEVLNM	0107	// CDU\X last in 5.03
#define	CALLI_PATHd	0110	// L,,A S J,,F F D C
#define	CALLI_METERd	0111	// L+1,,A S F
#define	CALLI_MTCHRd	0112	// L,,A CUD S
#define	CALLI_JBSETd	0113	// 2,,A S
#define	CALLI_POKEd	0114	// 3,,A S
#define	CALLI_TRMNOd	0115	// J S S
#define	CALLI_TRMOPd	0116	// L,,A S F\U
#define	CALLI_RESDVd	0117	// CU S
#define	CALLI_UNLOKd	0120	// X,,X S last in 5.04
#define	CALLI_DISKd	0121	// F,,A S
#define	CALLI_DVRSTd	0122	// CDU S
#define	CALLI_DVURSd	0123	// CDU S last in 5.05, 5.06
#define	CALLI_XTTSKd	0124	// ?
#define	CALLI_CAL11d	0125	// L,,A S
#define	CALLI_MTAIDd	0126	// CDU\X S
#define	CALLI_IONDXd	0127	// CD S
#define	CALLI_CNECTd	0130	// A S
#define	CALLI_MVHDRd	0131	//
#define	CALLI_ERLSTd	0132	//
#define	CALLI_SENSEd	0133	//
#define	CALLI_CLRSTd	0134	//
#define	CALLI_PIINId	0135	//
#define	CALLI_PISYSd	0136	//
#define	CALLI_DEBRKd	0137	//
#define	CALLI_PISAVd	0140	//
#define	CALLI_PIRSTd	0141	//
#define	CALLI_IPCFRd	0142	//
#define	CALLI_IPCFSd	0143	//
#define	CALLI_IPCFQd	0144	//
#define	CALLI_PAGEd	0145	//
#define	CALLI_SUSETd	0146	//
#define	CALLI_COMPTd	0147	// last in 5.07/6.01
#define	CALLI_SCHEDd	0150	//
#define	CALLI_ENQd	0151	//
#define	CALLI_DEQd	0152	//
#define	CALLI_ENQCd	0153	//
#define	CALLI_TAPOPd	0154	//
#define	CALLI_FILOPd	0155	//
#define	CALLI_CAL78d	0156	//
#define	CALLI_NODEd	0157	//
#define	CALLI_ERRPTd	0160	//
#define	CALLI_ALLOCd	0161	//
#define	CALLI_PERFd	0162	// last in 6.02
#define	CALLI_DIAGd	0163	//
#define	CALLI_DVPHYd	0164	//
#define	CALLI_GTNTNd	0165	//
#define	CALLI_GTXTNd	0166	//
#define	CALLI_ACCTd	0167	//
#define	CALLI_DTEd	0170	//
#define	CALLI_DEVOPd	0171	// last in 6.03
#define	CALLI_SPPRMd	0172	//
#define	CALLI_MERGEd	0173	//
#define	CALLI_UTRPd	0174	//
#define	CALLI_PIJBId	0175	//
#define	CALLI_SNOOPd	0176	//
#define	CALLI_TSKd	0177	//
#define	CALLI_KDPd	0200	//
#define	CALLI_QUEUEd	0201	//
#define	CALLI_RECONd	0202	// last in 7.01
#define	CALLI_PITMRd	0203	//
#define	CALLI_ACCLGd	0204	//
#define	CALLI_NSPd	0205	//
#define	CALLI_NTMANd	0206	//
#define	CALLI_DNETd	0207	//
#define	CALLI_SAVEd	0210	//
#define	CALLI_CMANDd	0211	//
#define	CALLI_PIBLKd	0212	//
#define	CALLI_SCSd	0213	//
#define	CALLI_SEBLKd	0214	// last in 7.02
#define	CALLI_CTXd	0215	//
#define	CALLI_PIFLGd	0216	//
#define	CALLI_IPCFMd	0217	//
#define	CALLI_LLMOPd	0220	//
#define	CALLI_LATOPd	0221	//
#define	CALLI_KNIBTd	0222	//
#define	CALLI_CHTRNd	0223	//
#define	CALLI_ETHNTd	0224	//
#define	CALLI_ENTVCd	0225	//
#define	CALLI_NETOPd	0226	// last in 7.03
#define	CALLI_DDPd	0227	//
#define	CALLI_SEGOPd	0230	// last in 7.04

// Prototypes

int t10_CALLI_LIGHTS(PCTX *ctx);
int t10_CALLI_RESET(PCTX *ctx);
int t10_CALLI_DDTIN(PCTX *ctx);
int t10_CALLI_SETDDT(PCTX *ctx);
int t10_CALLI_DDTOUT(PCTX *ctx);
int t10_CALLI_DEVCHR(PCTX *ctx);
int t10_CALLI_DDTGT(PCTX *ctx);
int t10_CALLI_GETCHR(PCTX *ctx);
int t10_CALLI_DDTRL(PCTX *ctx);
int t10_CALLI_WAIT(PCTX *ctx);
int t10_CALLI_CORE(PCTX *ctx);
int t10_CALLI_EXIT(PCTX *ctx);
int t10_CALLI_UTPCLR(PCTX *ctx);
int t10_CALLI_DATE(PCTX *ctx);
int t10_CALLI_LOGIN(PCTX *ctx);
int t10_CALLI_APRENB(PCTX *ctx);
int t10_CALLI_LOGOUT(PCTX *ctx);
int t10_CALLI_SWITCH(PCTX *ctx);
int t10_CALLI_REASSI(PCTX *ctx);
int t10_CALLI_TIMER(PCTX *ctx);
int t10_CALLI_MSTIME(PCTX *ctx);
int t10_CALLI_GETPPN(PCTX *ctx);
int t10_CALLI_TRPSET(PCTX *ctx);
int t10_CALLI_TRPJEN(PCTX *ctx);
int t10_CALLI_RUNTIM(PCTX *ctx);
int t10_CALLI_PJOB(PCTX *ctx);
int t10_CALLI_SLEEP(PCTX *ctx);
int t10_CALLI_SETPOV(PCTX *ctx);
int t10_CALLI_PEEK(PCTX *ctx);
int t10_CALLI_GETLIN(PCTX *ctx);
int t10_CALLI_RUN(PCTX *ctx);
int t10_CALLI_SETUWP(PCTX *ctx);
int t10_CALLI_REMAP(PCTX *ctx);
int t10_CALLI_GETSEG(PCTX *ctx);
int t10_CALLI_GETTAB(PCTX *ctx);
int t10_CALLI_SPY(PCTX *ctx);
int t10_CALLI_SETNAM(PCTX *ctx);
int t10_CALLI_TMPCOR(PCTX *ctx);
int t10_CALLI_DSKCHR(PCTX *ctx);
int t10_CALLI_SYSSTR(PCTX *ctx);
int t10_CALLI_JOBSTR(PCTX *ctx);
int t10_CALLI_STRUUO(PCTX *ctx);
int t10_CALLI_SYSPHY(PCTX *ctx);
int t10_CALLI_FRECHN(PCTX *ctx);
int t10_CALLI_DEVTYP(PCTX *ctx);
int t10_CALLI_DEVSTS(PCTX *ctx);
int t10_CALLI_DEVPPN(PCTX *ctx);
int t10_CALLI_SEEK(PCTX *ctx);
int t10_CALLI_RTTRP(PCTX *ctx);
int t10_CALLI_LOCK(PCTX *ctx);
int t10_CALLI_JOBSTS(PCTX *ctx);
int t10_CALLI_LOCATE(PCTX *ctx);
int t10_CALLI_WHERE(PCTX *ctx);
int t10_CALLI_DEVNAM(PCTX *ctx);
int t10_CALLI_CTLJOB(PCTX *ctx);
int t10_CALLI_GOBSTR(PCTX *ctx);
int t10_CALLI_ACTIVA(PCTX *ctx);
int t10_CALLI_DEACTI(PCTX *ctx);
int t10_CALLI_HPQ(PCTX *ctx);
int t10_CALLI_HIBER(PCTX *ctx);
int t10_CALLI_WAKE(PCTX *ctx);
int t10_CALLI_CHGPPN(PCTX *ctx);
int t10_CALLI_SETUUO(PCTX *ctx);
int t10_CALLI_DEVGEN(PCTX *ctx);
int t10_CALLI_OTHUSR(PCTX *ctx);
int t10_CALLI_CHKACC(PCTX *ctx);
int t10_CALLI_DEVSIZ(PCTX *ctx);
int t10_CALLI_DAEMON(PCTX *ctx);
int t10_CALLI_JOBPEK(PCTX *ctx);
int t10_CALLI_ATTACH(PCTX *ctx);
int t10_CALLI_DAEFIN(PCTX *ctx);
int t10_CALLI_FRCUUO(PCTX *ctx);
int t10_CALLI_DEVLNM(PCTX *ctx);
int t10_CALLI_PATHd(PCTX *ctx);
int t10_CALLI_METERd(PCTX *ctx);
int t10_CALLI_MTCHRd(PCTX *ctx);
int t10_CALLI_JBSETd(PCTX *ctx);
int t10_CALLI_POKEd(PCTX *ctx);
int t10_CALLI_TRMNOd(PCTX *ctx);
int t10_CALLI_TRMOPd(PCTX *ctx);
int t10_CALLI_RESDVd(PCTX *ctx);
int t10_CALLI_UNLOKd(PCTX *ctx);
int t10_CALLI_DISKd(PCTX *ctx);
int t10_CALLI_DVRSTd(PCTX *ctx);
int t10_CALLI_DVURSd(PCTX *ctx);
int t10_CALLI_XTTSKd(PCTX *ctx);
int t10_CALLI_CAL11d(PCTX *ctx);
int t10_CALLI_MTAIDd(PCTX *ctx);
int t10_CALLI_IONDXd(PCTX *ctx);
int t10_CALLI_CNECTd(PCTX *ctx);
int t10_CALLI_MVHDRd(PCTX *ctx);
int t10_CALLI_ERLSTd(PCTX *ctx);
int t10_CALLI_SENSEd(PCTX *ctx);
int t10_CALLI_CLRSTd(PCTX *ctx);
int t10_CALLI_PIINId(PCTX *ctx);
int t10_CALLI_PISYSd(PCTX *ctx);
int t10_CALLI_DEBRKd(PCTX *ctx);
int t10_CALLI_PISAVd(PCTX *ctx);
int t10_CALLI_PIRSTd(PCTX *ctx);
int t10_CALLI_IPCFRd(PCTX *ctx);
int t10_CALLI_IPCFSd(PCTX *ctx);
int t10_CALLI_IPCFQd(PCTX *ctx);
int t10_CALLI_PAGEd(PCTX *ctx);
int t10_CALLI_SUSETd(PCTX *ctx);
int t10_CALLI_COMPTd(PCTX *ctx);
int t10_CALLI_SCHEDd(PCTX *ctx);
int t10_CALLI_ENQd(PCTX *ctx);
int t10_CALLI_DEQd(PCTX *ctx);
int t10_CALLI_ENQCd(PCTX *ctx);
int t10_CALLI_TAPOPd(PCTX *ctx);
int t10_CALLI_FILOPd(PCTX *ctx);
int t10_CALLI_CAL78d(PCTX *ctx);
int t10_CALLI_NODEd(PCTX *ctx);
int t10_CALLI_ERRPTd(PCTX *ctx);
int t10_CALLI_ALLOCd(PCTX *ctx);
int t10_CALLI_PERFd(PCTX *ctx);
int t10_CALLI_DIAGd(PCTX *ctx);
int t10_CALLI_DVPHYd(PCTX *ctx);
int t10_CALLI_GTNTNd(PCTX *ctx);
int t10_CALLI_GTXTNd(PCTX *ctx);
int t10_CALLI_ACCTd(PCTX *ctx);
int t10_CALLI_DTEd(PCTX *ctx);
int t10_CALLI_DEVOPd(PCTX *ctx);
int t10_CALLI_SPPRMd(PCTX *ctx);
int t10_CALLI_MERGEd(PCTX *ctx);
int t10_CALLI_UTRPd(PCTX *ctx);
int t10_CALLI_PIJBId(PCTX *ctx);
int t10_CALLI_SNOOPd(PCTX *ctx);
int t10_CALLI_TSKd(PCTX *ctx);
int t10_CALLI_KDPd(PCTX *ctx);
int t10_CALLI_QUEUEd(PCTX *ctx);
int t10_CALLI_RECONd(PCTX *ctx);
int t10_CALLI_PITMRd(PCTX *ctx);
int t10_CALLI_ACCLGd(PCTX *ctx);
int t10_CALLI_NSPd(PCTX *ctx);
int t10_CALLI_NTMANd(PCTX *ctx);
int t10_CALLI_DNETd(PCTX *ctx);
int t10_CALLI_SAVEd(PCTX *ctx);
int t10_CALLI_CMANDd(PCTX *ctx);
int t10_CALLI_PIBLKd(PCTX *ctx);
int t10_CALLI_SCSd(PCTX *ctx);
int t10_CALLI_SEBLKd(PCTX *ctx);
int t10_CALLI_CTXd(PCTX *ctx);
int t10_CALLI_PIFLGd(PCTX *ctx);
int t10_CALLI_IPCFMd(PCTX *ctx);
int t10_CALLI_LLMOPd(PCTX *ctx);
int t10_CALLI_LATOPd(PCTX *ctx);
int t10_CALLI_KNIBTd(PCTX *ctx);
int t10_CALLI_CHTRNd(PCTX *ctx);
int t10_CALLI_ETHNTd(PCTX *ctx);
int t10_CALLI_ENTVCd(PCTX *ctx);
int t10_CALLI_NETOPd(PCTX *ctx);
int t10_CALLI_DDPd(PCTX *ctx);
int t10_CALLI_SEGOPd(PCTX *ctx);

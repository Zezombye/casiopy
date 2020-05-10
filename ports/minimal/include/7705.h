#ifndef	_7705_H
#define	_7705_H	1


// Internal Control Registers definition :

struct st_cpg {                                         /* struct CPG   */
              union {                                   /* FRQCR        */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :3;      /*              */
                           unsigned short CKOEN:1;      /*    CKOEN     */
                           unsigned short      :2;      /*              */
                           unsigned short STC  :2;      /*    STC       */
                           unsigned short      :2;      /*              */
                           unsigned short IFC  :2;      /*    IFC       */
                           unsigned short      :2;      /*              */
                           unsigned short _PFC :2;      /*    PFC       */
                           }       BIT;                 /*              */
                    }           FRQCR;                  /*              */
};                                                      /*              */
struct st_wdt {                                         /* struct WDT   */
              union {                                   /* WTCNT        */
                    unsigned char  READ;                /*  Read  Access*/
                    unsigned short WRITE;               /*  Write Access*/
                    }           WTCNT;                  /*              */
              union {                                   /* WTCSR        */
                    union {                             /*  Read  Access*/
                          unsigned char BYTE;           /*   Byte Access*/
                          struct {                      /*   Bit  Access*/
                                 unsigned char TME :1;  /*    TME       */
                                 unsigned char WTIT:1;  /*    WT/IT     */
                                 unsigned char RSTS:1;  /*    RSTS      */
                                 unsigned char WOVF:1;  /*    WOVF      */
                                 unsigned char IOVF:1;  /*    IOVF      */
                                 unsigned char CKS :3;  /*    CKS       */
                                 }      BIT;            /*              */
                         }         READ;                /*              */
                    unsigned short WRITE;               /*  Write Access*/
                    }           WTCSR;                  /*              */
};

struct st_pa {                                          /* struct PA    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pb {                                          /* struct PB    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pc {                                          /* struct PC    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pd {                                          /* struct PD    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pe {                                          /* struct PE    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pf {                                          /* struct PF    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pg {                                          /* struct PG    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_ph {                                          /* struct PH    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char   :1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pj {                                          /* struct PJ    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pk {                                          /* struct PK    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pl {                                          /* struct PL    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char   :4;           /*    Bit 7-4   */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_scp {                                         /* struct SCP   */
              union {                                   /*              */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char   :2;          /*    Bit 7,6   */
                           unsigned char B5:1;          /*    Bit 5     */
                           unsigned char B4:1;          /*    Bit 4     */
                           unsigned char B3:1;          /*    Bit 3     */
                           unsigned char B2:1;          /*    Bit 2     */
                           unsigned char B1:1;          /*    Bit 1     */
                           unsigned char B0:1;          /*    Bit 0     */
                           }      BIT;                  /*              */
                    }           DR;                     /*              */
};                                                      /*              */
struct st_pm {                                          /* struct PM    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char   :1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char   :1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */
struct st_pn {                                          /* struct PN    */
             union {                                    /*              */
                   unsigned char BYTE;                  /*  Byte Access */
                   struct {                             /*  Bit  Access */
                          unsigned char B7:1;           /*    Bit 7     */
                          unsigned char B6:1;           /*    Bit 6     */
                          unsigned char B5:1;           /*    Bit 5     */
                          unsigned char B4:1;           /*    Bit 4     */
                          unsigned char B3:1;           /*    Bit 3     */
                          unsigned char B2:1;           /*    Bit 2     */
                          unsigned char B1:1;           /*    Bit 1     */
                          unsigned char B0:1;           /*    Bit 0     */
                          }      BIT;                   /*              */
                   }            DR;                     /*              */
};                                                      /*              */

struct st_usb {                                         /* struct USB   */
              union {                                   /* UCLKCR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char USSCS:2;       /*    USSCS     */
                           unsigned char USBEN:1;       /*    USBEN     */
                           }      BIT;                  /*              */
                    }           UCLKCR;                 /*              */
              char              wk1[4063223];           /*              */
              unsigned char     EPDR0i;                 /* EPDR0i       */
              char              wk2[3];                 /*              */
              unsigned char     EPDR0o;                 /* EPDR0o       */
              char              wk3[3];                 /*              */
              unsigned char     EPDR0s;                 /* EPDR0s       */
              char              wk4[3];                 /*              */
              unsigned char     EPDR1;                  /* EPDR1        */
              char              wk5[3];                 /*              */
              unsigned char     EPDR2;                  /* EPDR2        */
              char              wk6[3];                 /*              */
              unsigned char     EPDR3;                  /* EPDR3        */
              char              wk7[3];                 /*              */
              union {                                   /* IFR0         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char BRST    :1;    /*    BRST      */
                           unsigned char EP1FULL :1;    /*    EP1FULL   */
                           unsigned char EP2TR   :1;    /*    EP2TR     */
                           unsigned char EP2EMPTY:1;    /*    EP2EMPTY  */
                           unsigned char SETUPTS :1;    /*    SETUPTS   */
                           unsigned char EP0oTS  :1;    /*    EP0oTS    */
                           unsigned char EP0iTR  :1;    /*    EP0iTR    */
                           unsigned char EP0iTS  :1;    /*    EP0iTS    */
                           }      BIT;                  /*              */
                    }           IFR0;                   /*              */
              char              wk8[3];                 /*              */
              union {                                   /* IFR1         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char       :4;      /*              */
                           unsigned char VBUSMN:1;      /*    VBUSMN    */
                           unsigned char EP3TS :1;      /*    EP3TS     */
                           unsigned char EP3TR :1;      /*    EP3TR     */
                           unsigned char VBUS  :1;      /*    VBUS      */
                           }      BIT;                  /*              */
                    }           IFR1;                   /*              */
              char              wk9[3];                 /*              */
              union {                                   /* TRG          */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char         :1;    /*              */
                           unsigned char EP3PKTE :1;    /*    EP3PKTE   */
                           unsigned char EP1RDFN :1;    /*    EP1RDFN   */
                           unsigned char EP2PKTE :1;    /*    EP2PKTE   */
                           unsigned char         :1;    /*              */
                           unsigned char EP0sRDFN:1;    /*    EP0sRDFN  */
                           unsigned char EP0oRDFN:1;    /*    EP0oRDFN  */
                           unsigned char EP0iPKTE:1;    /*    EP0iPKTE  */
                           }      BIT;                  /*              */
                    }           TRG;                    /*              */
              char              wk10[3];                /*              */
              union {                                   /* FCLR         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char        :1;     /*              */
                           unsigned char EP3CLR :1;     /*    EP3CLR    */
                           unsigned char EP1CLR :1;     /*    EP1CLR    */
                           unsigned char EP2CLR :1;     /*    EP2CLR    */
                           unsigned char        :2;     /*              */
                           unsigned char EP0oCLR:1;     /*    EP0oCLR   */
                           unsigned char EP0iCLR:1;     /*    EP0iCLR   */
                           }      BIT;                  /*              */
                    }           FCLR;                   /*              */
              char              wk11[3];                /*              */
              unsigned char     EPSZ0o;                 /* EPSZ0o       */
              char              wk12[3];                /*              */
              union {                                   /* DASTS        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char       :2;      /*              */
                           unsigned char EP3DE :1;      /*    EP3DE     */
                           unsigned char EP2DE :1;      /*    EP2DE     */
                           unsigned char       :3;      /*              */
                           unsigned char EP0iDE:1;      /*    EP0iDE    */
                           }      BIT;                  /*              */
                    }           DASTS;                  /*              */
              char              wk13[3];                /*              */
              union {                                   /* EPSTL        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char       :4;      /*              */
                           unsigned char EP3STL:1;      /*    EP3STL    */
                           unsigned char EP2STL:1;      /*    EP2STL    */
                           unsigned char EP1STL:1;      /*    EP1STL    */
                           unsigned char EP0STL:1;      /*    EP0STL    */
                           }      BIT;                  /*              */
                    }           EPSTL;                  /*              */
              char              wk14[3];                /*              */
              union {                                   /* IER0         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char BRST    :1;    /*    BRST      */
                           unsigned char EP1FULL :1;    /*    EP1FULL   */
                           unsigned char EP2TR   :1;    /*    EP2TR     */
                           unsigned char EP2EMPTY:1;    /*    EP2EMPTY  */
                           unsigned char SETUPTS :1;    /*    SETUPTS   */
                           unsigned char EP0oTS  :1;    /*    EP0oTS    */
                           unsigned char EP0iTR  :1;    /*    EP0iTR    */
                           unsigned char EP0iTS  :1;    /*    EP0iTS    */
                           }      BIT;                  /*              */
                    }           IER0;                   /*              */
              char              wk15[3];                /*              */
              union {                                   /* IER1         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char      :5;       /*              */
                           unsigned char EP3TS:1;       /*    EP3TS     */
                           unsigned char EP3TR:1;       /*    EP3TR     */
                           unsigned char VBUS :1;       /*    VBUS      */
                           }      BIT;                  /*              */
                    }           IER1;                   /*              */
              char              wk16[3];                /*              */
              unsigned char     EPSZ1;                  /* EPSZ1        */
              char              wk17[3];                /*              */
              union {                                   /* DMAR         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char        :6;     /*              */
                           unsigned char EP2DMAE:1;     /*    EP2DMAE   */
                           unsigned char EP1DMAE:1;     /*    EP1DMAE   */
                           }      BIT;                  /*              */
                    }           DMAR;                   /*              */
              char              wk18[3];                /*              */
              union {                                   /* ISR0         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char BRST    :1;    /*    BRST      */
                           unsigned char EP1FULL :1;    /*    EP1FULL   */
                           unsigned char EP2TR   :1;    /*    EP2TR     */
                           unsigned char EP2EMPTY:1;    /*    EP2EMPTY  */
                           unsigned char SETUPTS :1;    /*    SETUPTS   */
                           unsigned char EP0oTS  :1;    /*    EP0oTS    */
                           unsigned char EP0iTR  :1;    /*    EP0iTR    */
                           unsigned char EP0iTS  :1;    /*    EP0iTS    */
                           }      BIT;                  /*              */
                    }           ISR0;                   /*              */
              char              wk19[3];                /*              */
              union {                                   /* ISR1         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char      :5;       /*              */
                           unsigned char EP3TS:1;       /*    EP3TS     */
                           unsigned char EP3TR:1;       /*    EP3TR     */
                           unsigned char VBUS :1;       /*    VBUS      */
                           }      BIT;                  /*              */
                    }           ISR1;                   /*              */
              char              wk20[23];               /*              */
              union {                                   /* XVERCR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char        :6;     /*              */
                           unsigned char XVEROFF:1;     /*    XVEROFF   */
                           }      BIT;                  /*              */
                    }           XVERCR;                 /*              */
};
struct st_intc {                                        /* struct INTC  */
               union {                                  /* ICR0         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short NMIL:1;      /*    NMIL      */
                            unsigned short     :6;      /*              */
                            unsigned short NMIE:1;      /*    NMIE      */
                            }       BIT;                /*              */
                     }          ICR0;                   /*              */
               union {                                  /* IPRA         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short _TMU0:4;     /*    TMU0      */
                            unsigned short _TMU1:4;     /*    TMU1      */
                            unsigned short _TMU2:4;     /*    TMU2      */
                            unsigned short _RTC :4;     /*    RTC       */
                            }       BIT;                /*              */
                     }          IPRA;                   /*              */
               union {                                  /* IPRB         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short _WDT:4;      /*    WDT       */
                            unsigned short _REF:4;      /*    REF       */
                            }       BIT;                /*              */
                     }          IPRB;                   /*              */
               char             wk[234];                /*              */
               unsigned int     TRA;                    /* TRA          */
               unsigned int     EXPEVT;                 /* EXPEVT       */
               unsigned int     INTEVT;                 /* INTEVT       */
};
struct st_intx {                                        /* struct INTX  */
               unsigned int     INTEVT2;                /* INTEVT2      */
               union {                                  /* IRR0         */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char PINT0R:1;     /*    PINT0R    */
                            unsigned char PINT1R:1;     /*    PINT1R    */
                            unsigned char IRQ5R :1;     /*    IRQ5R     */
                            unsigned char IRQ4R :1;     /*    IRQ4R     */
                            unsigned char IRQ3R :1;     /*    IRQ3R     */
                            unsigned char IRQ2R :1;     /*    IRQ2R     */
                            unsigned char IRQ1R :1;     /*    IRQ1R     */
                            unsigned char IRQ0R :1;     /*    IRQ0R     */
                            }      BIT;                 /*              */
                     }          IRR0;                   /*              */
               char             wk1;                    /*              */
               union {                                  /* IRR1         */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char TXI0R:1;      /*    TXI0R     */
                            unsigned char      :1;      /*              */
                            unsigned char RXI0R:1;      /*    RXI0R     */
                            unsigned char ERI0R:1;      /*    ERI0R     */
                            unsigned char DEI3R:1;      /*    DEI3R     */
                            unsigned char DEI2R:1;      /*    DEI2R     */
                            unsigned char DEI1R:1;      /*    DEI1R     */
                            unsigned char DEI0R:1;      /*    DEI0R     */
                            }      BIT;                 /*              */
                     }          IRR1;                   /*              */
               char             wk2;                    /*              */
               union {                                  /* IRR2         */
                     unsigned char BYTE;                /*  Byte Access */
                     struct {                           /*  Bit  Access */
                            unsigned char      :3;      /*              */
                            unsigned char ADIR :1;      /*    ADIR      */
                            unsigned char TXI2R:1;      /*    TXI2R     */
                            unsigned char      :1;      /*              */
                            unsigned char RXI2R:1;      /*    RXI2R     */
                            unsigned char ERI2R:1;      /*    ERI2R     */
                            }      BIT;                 /*              */
                     }          IRR2;                   /*              */
               char             wk3[7];                 /*              */
               union {                                  /* ICR1         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short MAI   :1;    /*    MAI       */
                            unsigned short IRQLVL:1;    /*    IRQLVL    */
                            unsigned short BLMSK :1;    /*    BLMSK     */
                            unsigned short       :1;    /*              */
                            unsigned short IRQ5S :2;    /*    IRQ5S     */
                            unsigned short IRQ4S :2;    /*    IRQ4S     */
                            unsigned short IRQ3S :2;    /*    IRQ3S     */
                            unsigned short IRQ2S :2;    /*    IRQ2S     */
                            unsigned short IRQ1S :2;    /*    IRQ1S     */
                            unsigned short IRQ0S :2;    /*    IRQ0S     */
                            }       BIT;                /*              */
                     }          ICR1;                   /*              */
               union {                                  /* ICR2         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short PINT15S:1;   /*    PINT15S   */
                            unsigned short PINT14S:1;   /*    PINT14S   */
                            unsigned short PINT13S:1;   /*    PINT13S   */
                            unsigned short PINT12S:1;   /*    PINT12S   */
                            unsigned short PINT11S:1;   /*    PINT11S   */
                            unsigned short PINT10S:1;   /*    PINT10S   */
                            unsigned short PINT9S :1;   /*    PINT9S    */
                            unsigned short PINT8S :1;   /*    PINT8S    */
                            unsigned short PINT7S :1;   /*    PINT7S    */
                            unsigned short PINT6S :1;   /*    PINT6S    */
                            unsigned short PINT5S :1;   /*    PINT5S    */
                            unsigned short PINT4S :1;   /*    PINT4S    */
                            unsigned short PINT3S :1;   /*    PINT3S    */
                            unsigned short PINT2S :1;   /*    PINT2S    */
                            unsigned short PINT1S :1;   /*    PINT1S    */
                            unsigned short PINT0S :1;   /*    PINT0S    */
                            }       BIT;                /*              */
                     }          ICR2;                   /*              */
               union {                                  /* PINTER       */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short PINT15E:1;   /*    PINT15E   */
                            unsigned short PINT14E:1;   /*    PINT14E   */
                            unsigned short PINT13E:1;   /*    PINT13E   */
                            unsigned short PINT12E:1;   /*    PINT12E   */
                            unsigned short PINT11E:1;   /*    PINT11E   */
                            unsigned short PINT10E:1;   /*    PINT10E   */
                            unsigned short PINT9E :1;   /*    PINT9E    */
                            unsigned short PINT8E :1;   /*    PINT8E    */
                            unsigned short PINT7E :1;   /*    PINT7E    */
                            unsigned short PINT6E :1;   /*    PINT6E    */
                            unsigned short PINT5E :1;   /*    PINT5E    */
                            unsigned short PINT4E :1;   /*    PINT4E    */
                            unsigned short PINT3E :1;   /*    PINT3E    */
                            unsigned short PINT2E :1;   /*    PINT2E    */
                            unsigned short PINT1E :1;   /*    PINT1E    */
                            unsigned short PINT0E :1;   /*    PINT0E    */
                            }       BIT;                /*              */
                     }          PINTER;                 /*              */
               union {                                  /* IPRC         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short _IRQ3:4;     /*    IRQ3      */
                            unsigned short _IRQ2:4;     /*    IRQ2      */
                            unsigned short _IRQ1:4;     /*    IRQ1      */
                            unsigned short _IRQ0:4;     /*    IRQ0      */
                            }       BIT;                /*              */
                     }          IPRC;                   /*              */
               union {                                  /* IPRD         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short _PINT0_7 :4; /*    PINT0-7   */
                            unsigned short _PINT8_15:4; /*    PINT8-15  */
                            unsigned short _IRQ5    :4; /*    IRQ5      */
                            unsigned short _IRQ4    :4; /*    IRQ4      */
                            }       BIT;                /*              */
                     }          IPRD;                   /*              */
               union {                                  /* IPRE         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short _DMAC :4;    /*    DMAC      */
                            unsigned short _SCIF0:4;    /*    SCIF0     */
                            unsigned short _SCIF2:4;    /*    SCIF2     */
                            unsigned short _ADC  :4;    /*    ADC       */
                            }       BIT;                /*              */
                     }          IPRE;                   /*              */
               char             wk4[524260];            /*              */
               union {                                  /* IPRF         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short     :8;      /*              */
                            unsigned short _USB:4;      /*    USB       */
                            }       BIT;                /*              */
                     }          IPRF;                   /*              */
               union {                                  /* IPRG         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short _TPU0:4;     /*    TPU0      */
                            unsigned short _TPU1:4;     /*    TPU1      */
                            }       BIT;                /*              */
                     }          IPRG;                   /*              */
               union {                                  /* IPRH         */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short _TPU2:4;     /*    TPU2      */
                            unsigned short _TPU3:4;     /*    TPU3      */
                            }       BIT;                /*              */
                     }          IPRH;                   /*              */
}; 
struct st_scif {                                        /* struct SCIF  */
               union {                                  /* SCSMR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short     :5;      /*              */
                            unsigned short SRC :3;      /*    SRC       */
                            unsigned short CA  :1;      /*    CA        */
                            unsigned short CHR :1;      /*    CHR       */
                            unsigned short _PE :1;      /*    PE        */
                            unsigned short OE  :1;      /*    O/E       */
                            unsigned short STOP:1;      /*    STOP      */
                            unsigned short     :1;      /*              */
                            unsigned short CKS :2;      /*    CKS       */
                            }       BIT;                /*              */
                     }          SCSMR;                  /*              */
               char             wk1[2];                 /*              */
               unsigned char    SCBRR;                  /* SCBRR        */
               char             wk2[3];                 /*              */
               union {                                  /* SCSCR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short     :4;      /*              */
                            unsigned short TSIE:1;      /*    TSIE      */
                            unsigned short ERIE:1;      /*    ERIE      */
                            unsigned short BRIE:1;      /*    BRIE      */
                            unsigned short DRIE:1;      /*    DRIE      */
                            unsigned short TIE :1;      /*    TIE       */
                            unsigned short RIE :1;      /*    RIE       */
                            unsigned short TE  :1;      /*    TE        */
                            unsigned short RE  :1;      /*    RE        */
                            unsigned short     :2;      /*              */
                            unsigned short CKE :2;      /*    CKE       */
                            }       BIT;                /*              */
                     }          SCSCR;                  /*              */
               char             wk3[2];                 /*              */
               unsigned char    SCTDSR;                 /* SCTDSR       */
               char             wk4[3];                 /*              */
               union {                                  /* SCFER        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short    :2;       /*              */
                            unsigned short PER:6;       /*    PER       */
                            unsigned short    :2;       /*              */
                            unsigned short FER:6;       /*    FER       */
                            }       BIT;                /*              */
                     }          SCFER;                  /*              */
               char             wk5[2];                 /*              */
               union {                                  /* SCSSR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short     :6;      /*              */
                            unsigned short ORER:1;      /*    ORER      */
                            unsigned short TSF :1;      /*    TSF       */
                            unsigned short ER  :1;      /*    ER        */
                            unsigned short TEND:1;      /*    TEND      */
                            unsigned short TDFE:1;      /*    TDFE      */
                            unsigned short BRK :1;      /*    BRK       */
                            unsigned short FER :1;      /*    FER       */
                            unsigned short PER :1;      /*    PER       */
                            unsigned short RDF :1;      /*    RDF       */
                            unsigned short DR  :1;      /*    DR        */
                            }       BIT;                /*              */
                     }          SCSSR;                  /*              */
               char             wk6[2];                 /*              */
               union {                                  /* SCFCR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Bit  Access */
                            unsigned short TSE  :1;     /*    TSE       */
                            unsigned short TCRST:1;     /*    TCRST     */
                            unsigned short      :3;     /*              */
                            unsigned short RSTRG:3;     /*    RSTRG     */
                            unsigned short RTRG :2;     /*    RTRG      */
                            unsigned short TTRG :2;     /*    TTRG      */
                            unsigned short MCE  :1;     /*    MCE       */
                            unsigned short TFRST:1;     /*    TFRST     */
                            unsigned short RFRST:1;     /*    RFRST     */
                            unsigned short LOOP :1;     /*    LOOP      */
                            }       BIT;                /*              */
                     }          SCFCR;                  /*              */
               char             wk7[2];                 /*              */
               union {                                  /* SCFDR        */
                     unsigned short WORD;               /*  Word Access */
                     struct {                           /*  Byte Access */
                            unsigned short  :1;         /*              */
                            unsigned short T:7;         /*    T         */
                            unsigned short  :1;         /*              */
                            unsigned short R:7;         /*    R         */
                            }       BIT;                /*              */
                     }          SCFDR;                  /*              */
               char             wk8[2];                 /*              */
               unsigned char    SCFTDR;                 /* SCFTDR       */
               char             wk9[3];                 /*              */
               unsigned char    SCFRDR;                 /* SCFRDR       */
};                                                      /*              */
union un_stbcr3 {                                       /* union STBCR3 */
                unsigned char BYTE;                     /*  Byte Access */
                struct {                                /*  Bit  Access */
                       unsigned char _USB  :1;          /*    USB       */
                       unsigned char       :1;          /*              */
                       unsigned char _CMT  :1;          /*    CMT       */
                       unsigned char _TPU  :1;          /*    TPU       */
                       unsigned char _ADC  :1;          /*    ADC       */
                       unsigned char _IrDA :1;          /*    IrDA      */
                       unsigned char _SCIF2:1;          /*    SCIF2     */
                       unsigned char _SCIF0:1;          /*    SCIF0     */
                       }      BIT;                      /*              */
};                                                      /*              */
struct st_pfc {                                         /* struct PFC   */
              union {                                   /* PACR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PA7MD:2;      /*    PA7MD     */
                           unsigned short PA6MD:2;      /*    PA6MD     */
                           unsigned short PA5MD:2;      /*    PA5MD     */
                           unsigned short PA4MD:2;      /*    PA4MD     */
                           unsigned short PA3MD:2;      /*    PA3MD     */
                           unsigned short PA2MD:2;      /*    PA2MD     */
                           unsigned short PA1MD:2;      /*    PA1MD     */
                           unsigned short PA0MD:2;      /*    PA0MD     */
                           }       BIT;                 /*              */
                    }           PACR;                   /*              */
              union {                                   /* PBCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PB7MD:2;      /*    PB7MD     */
                           unsigned short PB6MD:2;      /*    PB6MD     */
                           unsigned short PB5MD:2;      /*    PB5MD     */
                           unsigned short PB4MD:2;      /*    PB4MD     */
                           unsigned short PB3MD:2;      /*    PB3MD     */
                           unsigned short PB2MD:2;      /*    PB2MD     */
                           unsigned short PB1MD:2;      /*    PB1MD     */
                           unsigned short PB0MD:2;      /*    PB0MD     */
                           }       BIT;                 /*              */
                    }           PBCR;                   /*              */
              union {                                   /* PCCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PC7MD:2;      /*    PC7MD     */
                           unsigned short PC6MD:2;      /*    PC6MD     */
                           unsigned short PC5MD:2;      /*    PC5MD     */
                           unsigned short PC4MD:2;      /*    PC4MD     */
                           unsigned short PC3MD:2;      /*    PC3MD     */
                           unsigned short PC2MD:2;      /*    PC2MD     */
                           unsigned short PC1MD:2;      /*    PC1MD     */
                           unsigned short PC0MD:2;      /*    PC0MD     */
                           }       BIT;                 /*              */
                    }           PCCR;                   /*              */
              union {                                   /* PDCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PD7MD:2;      /*    PD7MD     */
                           unsigned short PD6MD:2;      /*    PD6MD     */
                           unsigned short PD5MD:2;      /*    PD5MD     */
                           unsigned short PD4MD:2;      /*    PD4MD     */
                           unsigned short PD3MD:2;      /*    PD3MD     */
                           unsigned short PD2MD:2;      /*    PD2MD     */
                           unsigned short PD1MD:2;      /*    PD1MD     */
                           unsigned short PD0MD:2;      /*    PD0MD     */
                           }       BIT;                 /*              */
                    }           PDCR;                   /*              */
              union {                                   /* PECR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PE7MD:2;      /*    PE7MD     */
                           unsigned short PE6MD:2;      /*    PE6MD     */
                           unsigned short PE5MD:2;      /*    PE5MD     */
                           unsigned short PE4MD:2;      /*    PE4MD     */
                           unsigned short PE3MD:2;      /*    PE3MD     */
                           unsigned short PE2MD:2;      /*    PE2MD     */
                           unsigned short PE1MD:2;      /*    PE1MD     */
                           unsigned short PE0MD:2;      /*    PE0MD     */
                           }       BIT;                 /*              */
                    }           PECR;                   /*              */
              union {                                   /* PFCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PF7MD:2;      /*    PF7MD     */
                           unsigned short PF6MD:2;      /*    PF6MD     */
                           unsigned short PF5MD:2;      /*    PF5MD     */
                           unsigned short PF4MD:2;      /*    PF4MD     */
                           unsigned short PF3MD:2;      /*    PF3MD     */
                           unsigned short PF2MD:2;      /*    PF2MD     */
                           unsigned short PF1MD:2;      /*    PF1MD     */
                           unsigned short PF0MD:2;      /*    PF0MD     */
                           }       BIT;                 /*              */
                    }           PFCR;                   /*              */
              union {                                   /* PGCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PG7MD:2;      /*    PG7MD     */
                           unsigned short PG6MD:2;      /*    PG6MD     */
                           unsigned short PG5MD:2;      /*    PG5MD     */
                           unsigned short PG4MD:2;      /*    PG4MD     */
                           unsigned short PG3MD:2;      /*    PG3MD     */
                           unsigned short PG2MD:2;      /*    PG2MD     */
                           unsigned short PG1MD:2;      /*    PG1MD     */
                           unsigned short PG0MD:2;      /*    PG0MD     */
                           }       BIT;                 /*              */
                    }           PGCR;                   /*              */
              union {                                   /* PHCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :2;      /*              */
                           unsigned short PH6MD:2;      /*    PH6MD     */
                           unsigned short PH5MD:2;      /*    PH5MD     */
                           unsigned short PH4MD:2;      /*    PH4MD     */
                           unsigned short PH3MD:2;      /*    PH3MD     */
                           unsigned short PH2MD:2;      /*    PH2MD     */
                           unsigned short PH1MD:2;      /*    PH1MD     */
                           unsigned short PH0MD:2;      /*    PH0MD     */
                           }       BIT;                 /*              */
                    }           PHCR;                   /*              */
              union {                                   /* PJCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PJ7MD:2;      /*    PJ7MD     */
                           unsigned short PJ6MD:2;      /*    PJ6MD     */
                           unsigned short PJ5MD:2;      /*    PJ5MD     */
                           unsigned short PJ4MD:2;      /*    PJ4MD     */
                           unsigned short PJ3MD:2;      /*    PJ3MD     */
                           unsigned short PJ2MD:2;      /*    PJ2MD     */
                           unsigned short PJ1MD:2;      /*    PJ1MD     */
                           unsigned short PJ0MD:2;      /*    PJ0MD     */
                           }       BIT;                 /*              */
                    }           PJCR;                   /*              */
              union {                                   /* PKCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PK7MD:2;      /*    PK7MD     */
                           unsigned short PK6MD:2;      /*    PK6MD     */
                           unsigned short PK5MD:2;      /*    PK5MD     */
                           unsigned short PK4MD:2;      /*    PK4MD     */
                           unsigned short PK3MD:2;      /*    PK3MD     */
                           unsigned short PK2MD:2;      /*    PK2MD     */
                           unsigned short PK1MD:2;      /*    PK1MD     */
                           unsigned short PK0MD:2;      /*    PK0MD     */
                           }       BIT;                 /*              */
                    }           PKCR;                   /*              */
              union {                                   /* PLCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :8;      /*              */
                           unsigned short PL3MD:2;      /*    PL3MD     */
                           unsigned short PL2MD:2;      /*    PL2MD     */
                           unsigned short PL1MD:2;      /*    PL1MD     */
                           unsigned short PL0MD:2;      /*    PL0MD     */
                           }       BIT;                 /*              */
                    }           PLCR;                   /*              */
              union {                                   /* SCPCR        */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short       :4;     /*              */
                           unsigned short SCP5MD:2;     /*    SCP5MD    */
                           unsigned short SCP4MD:2;     /*    SCP4MD    */
                           unsigned short SCP3MD:2;     /*    SCP3MD    */
                           unsigned short SCP2MD:2;     /*    SCP2MD    */
                           unsigned short SCP1MD:2;     /*    SCP1MD    */
                           unsigned short SCP0MD:2;     /*    SCP0MD    */
                           }       BIT;                 /*              */
                    }           SCPCR;                  /*              */
              union {                                   /* PMCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short      :2;      /*              */
                           unsigned short PM6MD:2;      /*    PM6MD     */
                           unsigned short      :2;      /*              */
                           unsigned short PM4MD:2;      /*    PM4MD     */
                           unsigned short PM3MD:2;      /*    PM3MD     */
                           unsigned short PM2MD:2;      /*    PM2MD     */
                           unsigned short PM1MD:2;      /*    PM1MD     */
                           unsigned short PM0MD:2;      /*    PM0MD     */
                           }       BIT;                 /*              */
                    }           PMCR;                   /*              */
              union {                                   /* PNCR         */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short PN7MD:2;      /*    PN7MD     */
                           unsigned short PN6MD:2;      /*    PN6MD     */
                           unsigned short PN5MD:2;      /*    PN5MD     */
                           unsigned short PN4MD:2;      /*    PN4MD     */
                           unsigned short PN3MD:2;      /*    PN3MD     */
                           unsigned short PN2MD:2;      /*    PN2MD     */
                           unsigned short PN1MD:2;      /*    PN1MD     */
                           unsigned short PN0MD:2;      /*    PN0MD     */
                           }       BIT;                 /*              */
                    }           PNCR;                   /*              */
              char              wk1[327724];            /*              */
              union {                                   /* PECR2        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char      :1;       /*              */
                           unsigned char PE6MD:1;       /*    PE6MD     */
                           unsigned char PE5MD:1;       /*    PE5MD     */
                           unsigned char PE4MD:1;       /*    PE4MD     */
                           }       BIT;                 /*              */
                    }           PECR2;                  /*              */
              char              wk2;                    /*              */
              union {                                   /* PFCR2        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char      :4;       /*              */
                           unsigned char PF3MD:1;       /*    PF3MD     */
                           unsigned char PF2MD:1;       /*    PF2MD     */
                           unsigned char PF1MD:1;       /*    PF1MD     */
                           unsigned char PF0MD:1;       /*    PF0MD     */
                           }       BIT;                 /*              */
                    }           PFCR2;                  /*              */
              char              wk3[15];                /*              */
              union {                                   /* PNCR2        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char      :1;       /*              */
                           unsigned char PN6MD:1;       /*    PN6MD     */
                           unsigned char PN5MD:1;       /*    PN5MD     */
                           unsigned char PN4MD:1;       /*    PN4MD     */
                           unsigned char PN3MD:1;       /*    PN3MD     */
                           unsigned char PN2MD:1;       /*    PN2MD     */
                           unsigned char PN1MD:1;       /*    PN1MD     */
                           unsigned char PN0MD:1;       /*    PN0MD     */
                           }       BIT;                 /*              */
                    }           PNCR2;                  /*              */
};                                                      /*              */

struct st_mmu {
	union {
		unsigned int LONG;
		struct {
			unsigned int		:23;
			unsigned char SV	:1;
			unsigned char		:2;
			unsigned char RC	:2;
			unsigned char		:1;
			unsigned char TF	:1;
			unsigned char IX	:1;
			unsigned char AT	:1;
		} BIT;
	} MMUCR;

	char wk1[12];
	union {
		unsigned int LONG;
		struct {
			unsigned int VPN	:22;
			unsigned char		:2;
			unsigned char ASID	:8;
		} BIT;
	} PTEH;
		
	union {
		unsigned int LONG;
		struct {
			unsigned char		:3;
			unsigned int		:19;
			unsigned char		:1;
			unsigned char V		:1;
			unsigned char		:1;
			unsigned char PR	:2;
			unsigned char SZ	:1;
			unsigned char C		:1;
			unsigned char D		:1;
			unsigned char SH	:1;
			unsigned char		:1;
		} BIT;
	} PTEL;

	unsigned int TTB;
};


struct st_ubc {
	unsigned int BDRB;

	unsigned int BDMRB;
	
	union {
		unsigned int LONG;
		struct {
			unsigned short		:10;
			unsigned int BASMA	:1;
			unsigned int BASMB	:1;
			unsigned int		:4;
			unsigned int SCMFCA	:1;
			unsigned int SCMFCB	:1;
			unsigned int SCMFDA	:1;
			unsigned int SCMFDB	:1;
			unsigned int PCTE	:1;
			unsigned int PCBA	:1;
			unsigned int 		:2;
			unsigned int DBEB	:1;
			unsigned int PCBB	:1;
			unsigned int		:2;
			unsigned int SEQ	:1;
			unsigned int		:2;
			unsigned int ETBE	:1;
		} BIT;
	} BRCR;

	unsigned short BETR;

	char wk1[2];

	unsigned int BARB;

	unsigned int BAMRB;

	union {
		unsigned short WORD;
		struct {
			unsigned short		:8;
			unsigned short CDB	:2;
			unsigned short IDB	:2;
			unsigned short RWB	:2;
			unsigned short SZB	:2;
		} BIT;
	} BBRB;

	char wk2[2];

	union {
		unsigned int LONG;
		struct {
			unsigned int SVF	:1;
			unsigned char		:3;
			unsigned int BSA	:28;
		} BIT;
	} BRSR;

	unsigned int BARA;

	unsigned int BAMRA;

	union {
		unsigned short WORD;
		struct {
			unsigned short		:8;
			unsigned short CDA	:2;
			unsigned short IDA	:2;
			unsigned short RWA	:2;
			unsigned short SZA	:2;
		} BIT;
	} BBRA;

	char wk3[2];

	union {
		unsigned int LONG;
		struct {
			unsigned int DVF	:1;
			unsigned char		:3;
			unsigned int BDA	:28;
		} BIT;
	} BRDR;

	char wk4[36];

	unsigned char BASRA;

	char wk5[3];

	unsigned char BASRB;
};


union un_stbcr2 {
	unsigned char BYTE;
	struct {
		unsigned char _UDI		:1;
		unsigned char _UBC		:1;
		unsigned char _DMAC		:1;
		unsigned char 			:1;
		unsigned char _TLB		:1;
		unsigned char _CACHE		:1;
		unsigned char			:2;
	} BIT;
};



#define CPG	(*(volatile struct st_cpg	*)0xffffff80)
#define WDT	(*(volatile struct st_wdt	*)0xffffff84)
#define INTC	(*(volatile struct st_intc	*)0xfffffee0)
#define INTX	(*(volatile struct st_intx	*)0xa4000000)
#define PA	(*(volatile struct st_pa	*)0xa4000120)
#define PB	(*(volatile struct st_pb	*)0xa4000122)
#define PC	(*(volatile struct st_pc	*)0xa4000124)
#define PD	(*(volatile struct st_pd	*)0xa4000126)
#define PE	(*(volatile struct st_pe	*)0xa4000128)
#define PF	(*(volatile struct st_pf	*)0xa400012a)
#define PG	(*(volatile struct st_pg	*)0xa400012c)
#define PH	(*(volatile struct st_ph	*)0xa400012e)
#define PJ	(*(volatile struct st_pj	*)0xa4000130)
#define PK	(*(volatile struct st_pk	*)0xa4000132)
#define PL	(*(volatile struct st_pl	*)0xa4000134)
#define SCP	(*(volatile struct st_scp	*)0xa4000136)
#define PM	(*(volatile struct st_pm	*)0xa4000138)
#define PN	(*(volatile struct st_pn	*)0xa400013a)
#define USB	(*(volatile struct st_usb	*)0xa40a0008)
#define SCIF0	(*(volatile struct st_scif	*)0xa4400000)
#define SCIF2	(*(volatile struct st_scif	*)0xa4410000)
#define STBCR3	(*(volatile union  un_stbcr3	*)0xa40a0000)
#define PFC	(*(volatile struct st_pfc	*)0xa4000100)
#define TEA	(*(volatile unsigned int	*)0xfffffffc)
#define MMU	(*(volatile struct st_mmu	*)0xffffffe0)
#define UBC	(*(volatile struct st_ubc	*)0xffffff90)
#define STBCR2	(*(volatile union  un_stbcr2	*)0xffffff88)

#endif // _7705_H

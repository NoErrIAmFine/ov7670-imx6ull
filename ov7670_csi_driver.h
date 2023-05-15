#ifndef __OV7670_DRIVER_H
#define __OV7670_DRIVER_H

#define OV7670_I2C_ADDR 0x41

#define OV7670_CSI_DRIVER_NAME          "ov7670-csi"
#define OV7670_CSI_DRIVER_VERSION       "0.0.1"
#define OV7670_CSI_DRIVER_DESCRIPTION   "ov7670 driver in imx6ull,use csi"

#define MAX_VIDEO_MEM 16

#define NUM_FROMATS ARRAY_SIZE(formats)

/* imx6ull csi 寄存器偏移宏定义 */
#define CSI_CSICR1		0x0
#define CSI_CSICR2		0x4
#define CSI_CSICR3		0x8
#define CSI_STATFIFO	0xC
#define CSI_CSIRXFIFO	0x10
#define CSI_CSIRXCNT	0x14
#define CSI_CSISR		0x18

#define CSI_CSIDBG		0x1C
#define CSI_CSIDMASA_STATFIFO	0x20
#define CSI_CSIDMATS_STATFIFO	0x24
#define CSI_CSIDMASA_FB1	0x28
#define CSI_CSIDMASA_FB2	0x2C
#define CSI_CSIFBUF_PARA	0x30
#define CSI_CSIIMAG_PARA	0x34
#define CSI_CSICR18 0x48
#define CSI_CSICR19 0x4c

/* 位偏移 */
/* csi control reg 1 */
#define CSICR1_SWAP16_EN		(0x1 << 31)
#define CSICR1_EXT_VSYNC		(0x1 << 30)
#define CSICR1_EOF_INT_EN		(0x1 << 29)
#define CSICR1_PRP_IF_EN		(0x1 << 28)
#define CSICR1_CCIR_MODE		(0x1 << 27)
#define CSICR1_COF_INT_EN		(0x1 << 26)
#define CSICR1_SF_OR_INTEN		(0x1 << 25)
#define CSICR1_RF_OR_INTEN		(0x1 << 24)
#define CSICR1_SFF_DMA_DONE_INTEN  (0x1 << 22)
#define CSICR1_STATFF_INTEN	(0x1 << 21)
#define CSICR1_FB2_DMA_DONE_INTEN  (0x1 << 20)
#define CSICR1_FB1_DMA_DONE_INTEN  (0x1 << 19)
#define CSICR1_RXFF_INTEN	(0x1 << 18)
#define CSICR1_SOF_POL		(0x1 << 17)
#define CSICR1_SOF_INTEN	(0x1 << 16)
// #define CSICR1_MCLKDIV		(0xF << 12)
#define CSICR1_HSYNC_POL	(0x1 << 11)
#define CSICR1_CCIR_EN		(0x1 << 10)
#define CSICR1_MCLKEN		(0x1 << 9)
#define CSICR1_FCC			(0x1 << 8)
#define CSICR1_PACK_DIR	(0x1 << 7)
#define CSICR1_CLR_STATFIFO (0x1 << 6)
#define CSICR1_CLR_RXFIFO	(0x1 << 5)
#define CSICR1_GCLK_MODE	(0x1 << 4)
#define CSICR1_INV_DATA	(0x1 << 3)
#define CSICR1_INV_PCLK	(0x1 << 2)
#define CSICR1_REDGE		(0x1 << 1)
#define CSICR1_PIXEL_BIT	(0x1 << 0)

/* control reg 3 */
#define CSICR3_FRMCNT		(0xFFFF << 16)
#define CSICR3_FRMCNT_RST		(0x1 << 15)
#define CSICR3_DMA_REFLASH_RFF	(0x1 << 14)
#define CSICR3_DMA_REFLASH_SFF	(0x1 << 13)
#define CSICR3_DMA_REQ_EN_RFF	(0x1 << 12)
#define CSICR3_DMA_REQ_EN_SFF	(0x1 << 11)
#define CSICR3_STATFF_LEVEL	(0x7 << 8)
#define CSICR3_HRESP_ERR_EN	(0x1 << 7)
#define CSICR3_RXFF_LEVEL		(0x7 << 4)
#define CSICR3_TWO_8BIT_SENSOR	(0x1 << 3)
#define CSICR3_ZERO_PACK_EN	(0x1 << 2)
#define CSICR3_ECC_INT_EN		(0x1 << 1)
#define CSICR3_ECC_AUTO_EN		(0x1 << 0)

/* csi status reg */
#define CSISR_ADDR_CH_ERR_INT (0x1 << 28)
#define CSISR_FIELD0_INT      (0x1 << 27)
#define CSISR_FIELD1_INT      (0x1 << 26)
#define CSISR_SFF_OR_INT		(0x1 << 25)
#define CSISR_RFF_OR_INT		(0x1 << 24)
#define CSISR_DMA_TSF_DONE_SFF	(0x1 << 22)
#define CSISR_STATFF_INT		(0x1 << 21)
#define CSISR_DMA_TSF_DONE_FB2	(0x1 << 20)
#define CSISR_DMA_TSF_DONE_FB1	(0x1 << 19)
#define CSISR_RXFF_INT	(0x1 << 18)
#define CSISR_EOF_INT		(0x1 << 17)
#define CSISR_SOF_INT		(0x1 << 16)
#define CSISR_F2_INT		(0x1 << 15)
#define CSISR_F1_INT		(0x1 << 14)
#define CSISR_COF_INT		(0x1 << 13)
#define CSISR_HRESP_ERR_INT	(0x1 << 7)
#define CSISR_ECC_INT		(0x1 << 1)
#define CSISR_DRDY		(0x1 << 0)

/* csi cr18 */
#define CSICR18_CSI_ENABLE			(0x1 << 31)
#define CSICR18_MIPI_DATA_FORMAT_RAW8		(0x2a << 25)
#define CSICR18_MIPI_DATA_FORMAT_RAW10		(0x2b << 25)
#define CSICR18_MIPI_DATA_FORMAT_YUV422_8B	(0x1e << 25)
#define CSICR18_MIPI_DATA_FORMAT_MASK	    (0x3F << 25)
#define CSICR18_MIPI_DATA_FORMAT_OFFSET	25
#define CSICR18_DATA_FROM_MIPI		(0x1 << 22)
#define CSICR18_MIPI_YU_SWAP		(0x1 << 21)
#define CSICR18_MIPI_DOUBLE_CMPNT	(0x1 << 20)
#define CSICR18_BASEADDR_CHG_ERR_EN	(0x1 << 9)
#define CSICR18_BASEADDR_SWITCH_SEL	(0x1 << 5)
#define CSICR18_BASEADDR_SWITCH_EN	(0x1 << 4)
#define CSICR18_PARALLEL24_EN		(0x1 << 3)
#define CSICR18_DEINTERLACE_EN		(0x1 << 2)
#define CSICR18_TVDECODER_IN_EN		(0x1 << 1)
#define CSICR18_NTSC_EN				(0x1 << 0)

#define CSICR1_RESET_VALUE 0x40000800       //??这个值的含义有点搞不懂
#define CSICR2_RESET_VALUE 0x0
#define CSICR3_RESET_VALUE 0x0

/* ov7670 寄存器地址 */
/* Registers */
#define OV7670_REG_GAIN	0x00	            /* Gain lower 8 bits (rest in vref) */
#define OV7670_REG_BLUE	0x01	            /* blue gain */
#define OV7670_REG_RED		0x02	        /* red gain */
#define OV7670_REG_VREF	0x03	            /* Pieces of GAIN, VSTART, VSTOP */
#define OV7670_REG_COM1	0x04	            /* Control 1 */
#define   OV7670_COM1_CCIR656	  0x40      /* CCIR656 enable */
#define OV7670_REG_BAVE	0x05	            /* U/B Average level */
#define OV7670_REG_GbAVE	0x06	        /* Y/Gb Average level */
#define OV7670_REG_AECHH	0x07	        /* AEC MS 5 bits */
#define OV7670_REG_RAVE	0x08	            /* V/R Average level */
#define OV7670_REG_COM2	0x09	            /* Control 2 */
#define   OV7670_COM2_SSLEEP	  0x10	    /* Soft sleep mode */
#define OV7670_REG_PID		0x0a	        /* Product ID MSB */
#define OV7670_REG_VER		0x0b	        /* Product ID LSB */
#define OV7670_REG_COM3	0x0c	            /* Control 3 */
#define   OV7670_COM3_SWAP	  0x40	        /* Byte swap */
#define   OV7670_COM3_SCALEEN	  0x08	    /* Enable scaling */
#define   OV7670_COM3_DCWEN	  0x04	        /* Enable downsamp/crop/window */
#define OV7670_REG_COM4	0x0d	            /* Control 4 */
#define OV7670_REG_COM5	0x0e	            /* All "reserved" */
#define OV7670_REG_COM6	0x0f	            /* Control 6 */
#define OV7670_REG_AECH	0x10	            /* More bits of AEC value */
#define OV7670_REG_CLKRC	0x11	        /* Clocl control */
#define   OV7670_CLK_EXT	  0x40	        /* Use external clock directly */
#define   OV7670_CLK_SCALE	  0x3f	        /* Mask for internal clock scale */
#define OV7670_REG_COM7	0x12	            /* Control 7 */
#define   OV7670_COM7_RESET	  0x80	        /* Register reset */
#define   OV7670_COM7_FMT_MASK	  0x38
#define   OV7670_COM7_FMT_VGA	  0x00
#define	  OV7670_COM7_FMT_CIF	  0x20	    /* CIF format */
#define   OV7670_COM7_FMT_QVGA	  0x10	    /* QVGA format */
#define   OV7670_COM7_FMT_QCIF	  0x08	    /* QCIF format */
#define	  OV7670_COM7_RGB	  0x04	        /* bits 0 and 2 - RGB format */
#define	  OV7670_COM7_YUV	  0x00	        /* YUV */
#define	  OV7670_COM7_BAYER	  0x01	        /* Bayer format */
#define	  OV7670_COM7_PBAYER	  0x05	    /* "Processed bayer" */
#define OV7670_REG_COM8	0x13	            /* Control 8 */
#define   OV7670_COM8_FASTAEC	  0x80	    /* Enable fast AGC/AEC */
#define   OV7670_COM8_AECSTEP	  0x40	    /* Unlimited AEC step size */
#define   OV7670_COM8_BFILT	  0x20	        /* Band filter enable */
#define   OV7670_COM8_AGC	  0x04	        /* Auto gain enable */
#define   OV7670_COM8_AWB	  0x02	        /* White balance enable */
#define   OV7670_COM8_AEC	  0x01	        /* Auto exposure enable */
#define OV7670_REG_COM9	0x14	            /* Control 9  - gain ceiling */
#define OV7670_REG_COM10	0x15	        /* Control 10 */
#define   OV7670_COM10_HSYNC	  0x40	    /* HSYNC instead of HREF */
#define   OV7670_COM10_PCLK_HB	  0x20	    /* Suppress PCLK on horiz blank */
#define   OV7670_COM10_HREF_REV   0x08	    /* Reverse HREF */
#define   OV7670_COM10_VS_LEAD	  0x04	    /* VSYNC on clock leading edge */
#define   OV7670_COM10_VS_NEG	  0x02	    /* VSYNC negative */
#define   OV7670_COM10_HS_NEG	  0x01	    /* HSYNC negative */
#define OV7670_REG_HSTART	0x17	        /* Horiz start high bits */
#define OV7670_REG_HSTOP	0x18	        /* Horiz stop high bits */
#define OV7670_REG_VSTART	0x19	        /* Vert start high bits */
#define OV7670_REG_VSTOP	0x1a	        /* Vert stop high bits */
#define OV7670_REG_PSHFT	0x1b	        /* Pixel delay after HREF */
#define OV7670_REG_MIDH	0x1c	            /* Manuf. ID high */
#define OV7670_REG_MIDL	0x1d	            /* Manuf. ID low */
#define OV7670_REG_MVFP	0x1e	            /* Mirror / vflip */
#define   OV7670_MVFP_MIRROR	  0x20	    /* Mirror image */
#define   OV7670_MVFP_FLIP	  0x10	        /* Vertical flip */

#define OV7670_REG_AEW		0x24	        /* AGC upper limit */
#define OV7670_REG_AEB		0x25	        /* AGC lower limit */
#define OV7670_REG_VPT		0x26	        /* AGC/AEC fast mode op region */
#define OV7670_REG_HSYST	0x30	        /* HSYNC rising edge delay */
#define OV7670_REG_HSYEN	0x31	        /* HSYNC falling edge delay */
#define OV7670_REG_HREF	0x32	            /* HREF pieces */
#define OV7670_REG_TSLB	0x3a	            /* lots of stuff */
#define   OV7670_TSLB_YLAST	  0x04	        /* UYVY or VYUY - see com13 */
#define OV7670_REG_COM11	0x3b	        /* Control 11 */
#define   OV7670_COM11_NIGHT	  0x80	    /* NIght mode enable */
#define   OV7670_COM11_NMFR	  0x60	        /* Two bit NM frame rate */
#define   OV7670_COM11_HZAUTO	  0x10	    /* Auto detect 50/60 Hz */
#define	  OV7670_COM11_50HZ	  0x08	        /* Manual 50Hz select */
#define   OV7670_COM11_EXP	  0x02
#define OV7670_REG_COM12	0x3c	        /* Control 12 */
#define   OV7670_COM12_HREF	  0x80	        /* HREF always */
#define OV7670_REG_COM13	0x3d	        /* Control 13 */
#define   OV7670_COM13_GAMMA	  0x80	    /* Gamma enable */
#define	  OV7670_COM13_UVSAT	  0x40	    /* UV saturation auto adjustment */
#define   OV7670_COM13_UVSWAP	  0x01	    /* V before U - w/TSLB */
#define OV7670_REG_COM14	0x3e	        /* Control 14 */
#define   OV7670_COM14_DCWEN	  0x10	    /* DCW/PCLK-scale enable */
#define OV7670_REG_EDGE	0x3f	            /* Edge enhancement factor */
#define OV7670_REG_COM15	0x40	        /* Control 15 */
#define   OV7670_COM15_R10F0	  0x00	    /* Data range 10 to F0 */
#define	  OV7670_COM15_R01FE	  0x80	    /*            01 to FE */
#define   OV7670_COM15_R00FF	  0xc0	    /*            00 to FF */
#define   OV7670_COM15_RGB565	  0x10	    /* RGB565 output */
#define   OV7670_COM15_RGB555	  0x30	    /* RGB555 output */
#define OV7670_REG_COM16	0x41	        /* Control 16 */
#define   OV7670_COM16_AWBGAIN   0x08	    /* AWB gain enable */
#define OV7670_REG_COM17	0x42	        /* Control 17 */
#define   OV7670_COM17_AECWIN	  0xc0	    /* AEC window - must match COM4 */
#define   OV7670_COM17_CBAR	  0x08	        /* DSP Color bar */
#define	OV7670_REG_CMATRIX_BASE 0x4f
#define   OV7670_CMATRIX_LEN 6
#define OV7670_REG_CMATRIX_SIGN 0x58
#define OV7670_REG_BRIGHT	0x55	        /* Brightness */
#define OV7670_REG_CONTRAS	0x56	        /* Contrast control */
#define OV7670_REG_GFIX	0x69	            /* Fix gain control */
#define OV7670_REG_DBLV	0x6b	            /* PLL control an debugging */
#define   OV7670_DBLV_BYPASS	  0x00	    /* Bypass PLL */
#define   OV7670_DBLV_X4	  0x01	        /* clock x4 */
#define   OV7670_DBLV_X6	  0x10	        /* clock x6 */
#define   OV7670_DBLV_X8	  0x11	        /* clock x8 */
#define OV7670_REG_REG76	0x76	        /* OV's name */
#define   OV7670_R76_BLKPCOR	  0x80	    /* Black pixel correction enable */
#define   OV7670_R76_WHTPCOR	  0x40	    /* White pixel correction enable */
#define OV7670_REG_RGB444	0x8c	        /* RGB 444 control */
#define   OV7670_R444_ENABLE  0x02	        /* Turn on RGB444, overrides 5x5 */
#define   OV7670_R444_RGBX	  0x01	        /* Empty nibble at end */
#define OV7670_REG_HAECC1	0x9f	        /* Hist AEC/AGC control 1 */
#define OV7670_REG_HAECC2	0xa0	        /* Hist AEC/AGC control 2 */
#define OV7670_REG_BD50MAX	0xa5	        /* 50hz banding step limit */
#define OV7670_REG_HAECC3	0xa6	        /* Hist AEC/AGC control 3 */
#define OV7670_REG_HAECC4	0xa7	        /* Hist AEC/AGC control 4 */
#define OV7670_REG_HAECC5	0xa8	        /* Hist AEC/AGC control 5 */
#define OV7670_REG_HAECC6	0xa9	        /* Hist AEC/AGC control 6 */
#define OV7670_REG_HAECC7	0xaa	        /* Hist AEC/AGC control 7 */
#define OV7670_REG_BD60MAX	0xab	        /* 60hz banding step limit */

/*
 * This matrix defines how the colors are generated, must be
 * tweaked to adjust hue and saturation.
 *
 * Order: v-red, v-green, v-blue, u-red, u-green, u-blue
 *
 * They are nine-bit signed quantities, with the sign bit
 * stored in 0x58.  Sign for v-red is bit 0, and up from there.
 */
#define	OV7670_REG_CMATRIX_BASE 0x4f
#define   CMATRIX_LEN 6
#define OV7670_REG_CMATRIX_SIGN 0x58

#define OV7670_REG_REG76	0x76	/* OV's name */
#define   OV7670_R76_BLKPCOR	  0x80	  /* Black pixel correction enable */
#define   OV7670_R76_WHTPCOR	  0x40	  /* White pixel correction enable */

#define OV7670_REG_RGB444	0x8c	/* RGB 444 control */
#define   OV7670_R444_ENABLE	  0x02	  /* Turn on RGB444, overrides 5x5 */
#define   OV7670_R444_RGBX	  0x01	  /* Empty nibble at end */

#define OV7670_REG_HAECC1	0x9f	/* Hist AEC/AGC control 1 */
#define OV7670_REG_HAECC2	0xa0	/* Hist AEC/AGC control 2 */

#define OV7670_REG_BD50MAX	0xa5	/* 50hz banding step limit */
#define OV7670_REG_HAECC3	0xa6	/* Hist AEC/AGC control 3 */
#define OV7670_REG_HAECC4	0xa7	/* Hist AEC/AGC control 4 */
#define OV7670_REG_HAECC5	0xa8	/* Hist AEC/AGC control 5 */
#define OV7670_REG_HAECC6	0xa9	/* Hist AEC/AGC control 6 */
#define OV7670_REG_HAECC7	0xaa	/* Hist AEC/AGC control 7 */
#define OV7670_REG_BD60MAX	0xab	/* 60hz banding step limit */

struct reg_value
{
    u8 addr;
    u8 value;
};

struct ov7670_buf_internal
{
    struct list_head queue;
    int buf_num;
    bool discard;
};

struct ov7670_csi_buffer
{
    struct vb2_buffer vb;
    struct ov7670_buf_internal internal;
};

/*
 * Store information about the video data format.  The color matrix
 * is deeply tied into the format, so keep the relevant values here.
 * The magic matrix numbers come from OmniVision.
 */
struct ov7670_csi_format
{
    char name[32];
    u32 fourcc;
    u32 pixelformat;
    int bpp;
    enum v4l2_colorspace colorspace;
	struct reg_value *regs;
	int cmatrix[CMATRIX_LEN];
};

struct ov7670_data_fromat
{
    u32 code;
    enum v4l2_colorspace colorspace;
};

struct ov7670_win_size {
	int	width;
	int	height;
	unsigned char com7_bit;
	int	hstart;		            /* Start/stop values for the camera.  Note */
	int	hstop;		            /* that they do not always make complete */
	int	vstart;		            /* sense to humans, but evidently the sensor */
	int	vstop;		            /* will do the right thing... */
	struct reg_value *regs;     /* Regs to tweak */
};


struct ov7670_csi_dev
{
    struct device *dev;
    struct video_device *vdev;
    struct v4l2_subdev *sdev;
    struct v4l2_device v4l2_dev;

    struct vb2_queue vb2_q;
    void *alloc_ctx;
    struct v4l2_ctrl_handler ctrl_handler;
    
    struct mutex lock;
    spinlock_t slock;

    /* clocks */
    struct clk *clk_csi_mclk;
    struct clk *clk_disp_axi;
    struct clk *clk_disp_dcic;
    /* 提供给ov7670的主时钟，注意（imx6ul手册）：
     * MCLK is provided by the CCM module directly, not from the CSI module itself" */
    struct clk *clk_csi_ov7670_sel;
    struct clk *clk_csi_ov7670_podf;

    void __iomem *reg_base;
    unsigned long reg_addr_base;
    unsigned long reg_addr_size;
    int irq;

    unsigned int frame_count;
    struct list_head capture;
    struct list_head active_bufs;
    struct list_head discard;

    void *discard_buffer;
    dma_addr_t discard_buffer_dma;
    size_t discard_size;
    struct ov7670_buf_internal buf_discard[2];

    /* 当前所使用的格式 */
    u32 type;
    v4l2_std_id std;
    const struct ov7670_csi_format *fmt;
    struct v4l2_pix_format pix;

    struct i2c_client *client;

    /* 复位和节能引脚所对应的gpio */
    struct gpio_desc *reset_gpio;
    struct gpio_desc *pwdn_gpio;
};

#endif // !__OV7670_DRIVER_H

#include <linux/busfreq-imx.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/gpio/consumer.h>
#include <linux/interrupt.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/pm_runtime.h>
#include <linux/delay.h>

#include <media/v4l2-dev.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-core.h>
#include <media/videobuf2-dma-contig.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-image-sizes.h>

#include <asm/io.h>
#include <asm/dma-mapping.h>

#include "ov7670_csi_driver.h"

#if 0 
/* 摄像头出售店铺提供的代码 */
static struct reg_value ov7670_default_regs[] = {
    {0x3a, 0x04},{0x40, 0xd0},{0x12, 0x14},{0x32, 0x80},
	{0x17, 0x16},{0x18, 0x04},{0x19, 0x02},{0x1a, 0x7b},
	{0x03, 0x06},{0x0c, 0x04},{0x3e, 0x00},{0x70, 0x3a},
	{0x71, 0x35},{0x72, 0x11},{0x73, 0x00},{0xa2, 0x02},
    {0x11, 0x81},
	
    {0x7a, 0x20},{0x7b, 0x1c},{0x7c, 0x28},{0x7d, 0x3c},
	{0x7e, 0x55},{0x7f, 0x68},{0x80, 0x76},{0x81, 0x80},
    {0x82, 0x88},{0x83, 0x8f},{0x84, 0x96},{0x85, 0xa3},
	{0x86, 0xaf},{0x87, 0xc4},{0x88, 0xd7},{0x89, 0xe8},
	
	{0x13, 0xe0},{0x00, 0x00},
	
    {0x10, 0x00},{0x0d, 0x00},{0x14, 0x28},{0xa5, 0x05},
	{0xab, 0x07},{0x24, 0x75},{0x25, 0x63},{0x26, 0xA5},
	{0x9f, 0x78},{0xa0, 0x68},{0xa1, 0x03},{0xa6, 0xdf},
	{0xa7, 0xdf},{0xa8, 0xf0},{0xa9, 0x90},{0xaa, 0x94},
	{0x13, 0xe5},

	{0x0e, 0x61},{0x0f, 0x4b},{0x16, 0x02},{0x1e, 0x07},
	{0x21, 0x02},{0x22, 0x91},{0x29, 0x07},{0x33, 0x0b},
	{0x35, 0x0b},{0x37, 0x1d},{0x38, 0x71},{0x39, 0x2a},
	{0x3c, 0x78},{0x4d, 0x40},{0x4e, 0x20},{0x69, 0x00},
	
    {0x6b, 0x60},
    
    {0x74, 0x19},{0x8d, 0x4f},{0x8e, 0x00},
	{0x8f, 0x00},{0x90, 0x00},{0x91, 0x00},{0x92, 0x00},
    {0x96, 0x00},{0x9a, 0x80},{0xb0, 0x84},{0xb1, 0x0c},
    {0xb2, 0x0e},{0xb3, 0x82},{0xb8, 0x0a},

	{0x43, 0x14},{0x44, 0xf0},{0x45, 0x34},{0x46, 0x58},
	{0x47, 0x28},{0x48, 0x3a},{0x59, 0x88},{0x5a, 0x88},
	{0x5b, 0x44},{0x5c, 0x67},{0x5d, 0x49},{0x5e, 0x0e},
	{0x64, 0x04},{0x65, 0x20},{0x66, 0x05},{0x94, 0x04},
    {0x95, 0x08},{0x6c, 0x0a},{0x6d, 0x55},{0x6e, 0x11},
	{0x6f, 0x9f},{0x6a, 0x40},{0x01, 0x40},{0x02, 0x40},
	{0x13, 0xe7},{0x15, 0x00},  
	
	{0x4f, 0x80},{0x50, 0x80},{0x51, 0x00},{0x52, 0x22},
	{0x53, 0x5e},{0x54, 0x80},{0x58, 0x9e},
	
	{0x41, 0x08},{0x3f, 0x00},{0x75, 0x05},{0x76, 0xe1},
    {0x4c, 0x00},{0x77, 0x01},{0x3d, 0xc2},	{0x4b, 0x09},
	{0xc9, 0x60},{0x41, 0x38},{0x56, 0x40},
	
	{0x34, 0x11},{0x3b, 0x02}, 
					
	{0xa4, 0x89},{0x96, 0x00},{0x97, 0x30},{0x98, 0x20},
	{0x99, 0x30},{0x9a, 0x84},{0x9b, 0x29},{0x9c, 0x03},
	{0x9d, 0x4c},{0x9e, 0x3f},{0x78, 0x04},
	
	{0x79, 0x01},{0xc8, 0xf0},{0x79, 0x0f},{0xc8, 0x00},
	{0x79, 0x10},{0xc8, 0x7e},{0x79, 0x0a},{0xc8, 0x80},
	{0x79, 0x0b},{0xc8, 0x01},{0x79, 0x0c},{0xc8, 0x0f},
	{0x79, 0x0d},{0xc8, 0x20},{0x79, 0x09},{0xc8, 0x80},
	{0x79, 0x02},{0xc8, 0xc0},{0x79, 0x03},{0xc8, 0x40},
	{0x79, 0x05},{0xc8, 0x30},{0x79, 0x26},{0x09, 0x00},
    { 0xff, 0xff },     /* 结束标记 */
};
#else
/* 来自内核的初始化代码 */ 
static struct reg_value ov7670_default_regs[] = {
	{ OV7670_REG_COM7, 0x04},   //{ OV7670_REG_COM7, OV7670_COM7_RESET },
/*
 * Clock scale: 3 = 15fps
 *              2 = 20fps
 *              1 = 30fps
 */
	{ OV7670_REG_CLKRC, 0x41 },	/* OV: clock scale (30 fps) */
	{ OV7670_REG_TSLB,  0x04 },	/* OV */
	{ OV7670_REG_COM7, 0 },	/* VGA */
	/*
	 * Set the hardware window.  These values from OV don't entirely
	 * make sense - hstop is less than hstart.  But they work...
	 */
	{ OV7670_REG_HSTART, 0x16 },	{ OV7670_REG_HSTOP, 0x04 },
	{ OV7670_REG_HREF, 0x80 },	{ OV7670_REG_VSTART, 0x02 },
	{ OV7670_REG_VSTOP, 0x7b },	{ OV7670_REG_VREF, 0x06 },

	{ OV7670_REG_COM3, 0x00 },	{ OV7670_REG_COM14, 0x0 },
	/* Mystery scaling numbers */
	{ 0x70, 0x3a },		{ 0x71, 0x35 },
	{ 0x72, 0x11 },		{ 0x73, 0x00 },
	{ 0xa2, 0x02 },		{ OV7670_REG_COM10, 0x0 },

	/* Gamma curve values */
	{ 0x7a, 0x20 },		{ 0x7b, 0x1c },
	{ 0x7c, 0x28 },		{ 0x7d, 0x3c },
	{ 0x7e, 0x55 },		{ 0x7f, 0x68 },
	{ 0x80, 0x76 },		{ 0x81, 0x80 },
	{ 0x82, 0x88 },		{ 0x83, 0x8f },
	{ 0x84, 0x96 },		{ 0x85, 0xa3 },
	{ 0x86, 0xaf },		{ 0x87, 0xc4 },
	{ 0x88, 0xd7 },		{ 0x89, 0xe8 },

	/* AGC and AEC parameters.  Note we start by disabling those features,
	   then turn them only after tweaking the values. */
	{ OV7670_REG_COM8, 0 },     //{ OV7670_REG_COM8, OV7670_COM8_FASTAEC | OV7670_COM8_AECSTEP | OV7670_COM8_BFILT },
	{ OV7670_REG_GAIN, 0 },	{ OV7670_REG_AECH, 0 },
	{ OV7670_REG_COM4, 0x00 }, /* magic reserved bit */
	{ OV7670_REG_COM9, 0x28 }, /* 4x gain + magic rsvd bit */
	{ OV7670_REG_BD50MAX, 0x05 },	{ OV7670_REG_BD60MAX, 0x07 },
	{ OV7670_REG_AEW, 0x75 },	{ OV7670_REG_AEB, 0x63 },
	{ OV7670_REG_VPT, 0xa5 },	{ OV7670_REG_HAECC1, 0x78 },
	{ OV7670_REG_HAECC2, 0x68 },	{ 0xa1, 0x03 }, /* magic */
	{ OV7670_REG_HAECC3, 0xdf },	{ OV7670_REG_HAECC4, 0xdf },
	{ OV7670_REG_HAECC5, 0xf0 },	{ OV7670_REG_HAECC6, 0x90 },
	{ OV7670_REG_HAECC7, 0x94 },
	{ OV7670_REG_COM8, 0xe5 },     //{ OV7670_REG_COM8, OV7670_COM8_FASTAEC | OV7670_COM8_AECSTEP | OV7670_COM8_BFILT | OV7670_COM8_AGC | OV7670_COM8_AEC },

	/* Almost all of these are magic "reserved" values.  */
	{ OV7670_REG_COM5, 0x61 },	{ OV7670_REG_COM6, 0x4b },
	{ 0x16, 0x02 },		{ OV7670_REG_MVFP, 0x07 },
	{ 0x21, 0x02 },		{ 0x22, 0x91 },
	{ 0x29, 0x07 },		{ 0x33, 0x0b },
	{ 0x35, 0x0b },		{ 0x37, 0x1d },
	{ 0x38, 0x71 },		{ 0x39, 0x2a },
	{ OV7670_REG_COM12, 0x78 },	{ 0x4d, 0x40 },
	{ 0x4e, 0x20 },		{ OV7670_REG_GFIX, 0 },
	{ 0x6b, 0x60 },		{ 0x74, 0x19 },
	{ 0x8d, 0x4f },		{ 0x8e, 0 },
	{ 0x8f, 0 },		{ 0x90, 0 },
	{ 0x91, 0 },		{ 0x92, 0 },    { 0x96, 0 },
	{ 0x9a, 0x80 },		{ 0xb0, 0x84 },
	{ 0xb1, 0x0c },		{ 0xb2, 0x0e },
	{ 0xb3, 0x82 },		{ 0xb8, 0x0a },

	/* More reserved magic, some of which tweaks white balance */
	{ 0x43, 0x14 },		{ 0x44, 0xf0 },
	{ 0x45, 0x34 },		{ 0x46, 0x58 },
	{ 0x47, 0x28 },		{ 0x48, 0x3a },
	{ 0x59, 0x88 },		{ 0x5a, 0x88 },
	{ 0x5b, 0x44 },		{ 0x5c, 0x67 },
	{ 0x5d, 0x49 },		{ 0x5e, 0x0e },
    { 0x64, 0x04 },		{ 0x65, 0x20 },
    { 0x66, 0x05 },		{ 0x94, 0x04 },
    { 0x95, 0x08 },
	{ 0x6c, 0x0a },		{ 0x6d, 0x55 },
	{ 0x6e, 0x11 },		{ 0x6f, 0x9f }, /* "9e for advance AWB" */
	{ 0x6a, 0x40 },		{ OV7670_REG_BLUE, 0x40 },
	{ OV7670_REG_RED, 0x40 },
	{ OV7670_REG_COM8, OV7670_COM8_FASTAEC | OV7670_COM8_AECSTEP | OV7670_COM8_BFILT | OV7670_COM8_AGC | OV7670_COM8_AEC | OV7670_COM8_AWB },
    { 0x15, 0x00 },

	/* Matrix coefficients */
	{ 0x4f, 0x80 },		{ 0x50, 0x80 },
	{ 0x51, 0 },		{ 0x52, 0x22 },
	{ 0x53, 0x5e },		{ 0x54, 0x80 },
	{ 0x58, 0x9e },

	{ OV7670_REG_COM16, OV7670_COM16_AWBGAIN },	{ OV7670_REG_EDGE, 0 },
	{ 0x75, 0x05 },		{ 0x76, 0xe1 },
	{ 0x4c, 0 },		{ 0x77, 0x01 },
	{ OV7670_REG_COM13, 0xc2 },	{ 0x4b, 0x09 },
	{ 0xc9, 0x60 },		{ OV7670_REG_COM16, 0x38 },
	{ 0x56, 0x40 },

	{ 0x34, 0x11 },		//{ OV7670_REG_COM11, OV7670_COM11_EXP | OV7670_COM11_HZAUTO },
    { 0x3b, 0x02 },

	{ 0xa4, 0x89 },		{ 0x96, 0 },
	{ 0x97, 0x30 },		{ 0x98, 0x20 },
	{ 0x99, 0x30 },		{ 0x9a, 0x84 },
	{ 0x9b, 0x29 },		{ 0x9c, 0x03 },
	{ 0x9d, 0x4c },		{ 0x9e, 0x3f },
	{ 0x78, 0x04 },

	/* Extra-weird stuff.  Some sort of multiplexor register */
	{ 0x79, 0x01 },		{ 0xc8, 0xf0 },
	{ 0x79, 0x0f },		{ 0xc8, 0x00 },
	{ 0x79, 0x10 },		{ 0xc8, 0x7e },
	{ 0x79, 0x0a },		{ 0xc8, 0x80 },
	{ 0x79, 0x0b },		{ 0xc8, 0x01 },
	{ 0x79, 0x0c },		{ 0xc8, 0x0f },
	{ 0x79, 0x0d },		{ 0xc8, 0x20 },
	{ 0x79, 0x09 },		{ 0xc8, 0x80 },
	{ 0x79, 0x02 },		{ 0xc8, 0xc0 },
	{ 0x79, 0x03 },		{ 0xc8, 0x40 },
	{ 0x79, 0x05 },		{ 0xc8, 0x30 },
	{ 0x79, 0x26 },
    { 0x09, 0x00 },

	{ 0xff, 0xff },	/* END MARKER */
};
#endif

static struct reg_value ov7670_fmt_yuv422[] = {
	{ OV7670_REG_COM7, 0x0 },  /* Selects YUV mode */
	{ OV7670_REG_RGB444, 0 },	/* No RGB444 please */
	{ OV7670_REG_COM1, 0 },	/* CCIR601 */
	{ OV7670_REG_COM15, OV7670_COM15_R00FF },
	{ OV7670_REG_COM9, 0x48 }, /* 32x gain ceiling; 0x8 is reserved bit */
	{ 0x4f, 0x80 }, 	/* "matrix coefficient 1" */
	{ 0x50, 0x80 }, 	/* "matrix coefficient 2" */
	{ 0x51, 0    },		/* vb */
	{ 0x52, 0x22 }, 	/* "matrix coefficient 4" */
	{ 0x53, 0x5e }, 	/* "matrix coefficient 5" */
	{ 0x54, 0x80 }, 	/* "matrix coefficient 6" */
	{ OV7670_REG_COM13, OV7670_COM13_GAMMA | OV7670_COM13_UVSAT },
	{ 0xff, 0xff },
};

static struct reg_value ov7670_fmt_rgb565[] = {
	{ OV7670_REG_COM7, OV7670_COM7_RGB },	/* Selects RGB mode */
	{ OV7670_REG_RGB444, 0 },	/* No RGB444 please */
	{ OV7670_REG_COM1, 0x0 },	/* CCIR601 */
	{ OV7670_REG_COM15, OV7670_COM15_RGB565 },
	{ OV7670_REG_COM9, 0x38 }, 	/* 16x gain ceiling; 0x8 is reserved bit */
	{ 0x4f, 0xb3 }, 	/* "matrix coefficient 1" */
	{ 0x50, 0xb3 }, 	/* "matrix coefficient 2" */
	{ 0x51, 0    },		/* vb */
	{ 0x52, 0x3d }, 	/* "matrix coefficient 4" */
	{ 0x53, 0xa7 }, 	/* "matrix coefficient 5" */
	{ 0x54, 0xe4 }, 	/* "matrix coefficient 6" */
	{ OV7670_REG_COM13, OV7670_COM13_GAMMA|OV7670_COM13_UVSAT },
	{ 0xff, 0xff },
};

/* 内核中的代码，原来是rgb444 */
static struct reg_value ov7670_fmt_rgb555[] = {
	{ OV7670_REG_COM7, OV7670_COM7_RGB },	/* Selects RGB mode */
	{ OV7670_REG_RGB444, OV7670_R444_ENABLE },	/* Enable xxxxrrrr ggggbbbb */
	{ OV7670_REG_COM1, 0x0 },	/* CCIR601 */
	{ OV7670_REG_COM15, OV7670_COM15_R01FE | OV7670_COM15_RGB565 }, /* Data range needed? */
	{ OV7670_REG_COM9, 0x38 }, 	/* 16x gain ceiling; 0x8 is reserved bit */
	{ 0x4f, 0xb3 }, 	/* "matrix coefficient 1" */
	{ 0x50, 0xb3 }, 	/* "matrix coefficient 2" */
	{ 0x51, 0    },		/* vb */
	{ 0x52, 0x3d }, 	/* "matrix coefficient 4" */
	{ 0x53, 0xa7 }, 	/* "matrix coefficient 5" */
	{ 0x54, 0xe4 }, 	/* "matrix coefficient 6" */
	{ OV7670_REG_COM13, OV7670_COM13_GAMMA | OV7670_COM13_UVSAT|0x2 },  /* Magic rsvd bit */
	{ 0xff, 0xff },
};

static struct reg_value ov7670_fmt_raw[] = {
	{ OV7670_REG_COM7, OV7670_COM7_BAYER },
	{ OV7670_REG_COM13, 0x08 }, /* No gamma, magic rsvd bit */
	{ OV7670_REG_COM16, 0x3d }, /* Edge enhancement, denoise */
	{ OV7670_REG_REG76, 0xe1 }, /* Pix correction, magic rsvd */
	{ 0xff, 0xff },
};

static struct ov7670_csi_format formats[] = {
    {
        .name = "RGB-565",
        .fourcc = V4L2_PIX_FMT_RGB565,
        .pixelformat = V4L2_PIX_FMT_RGB565,
        .bpp = 2,
        .colorspace = V4L2_COLORSPACE_SRGB,
        .regs = ov7670_fmt_rgb565,
        .cmatrix = { 179, -179, 0, -61, -176, 228 },
    },
    {
        //ov7670手册上是有这种模式的，但在内核的代码中的却是rgb444
        //此处用的还是内核中的代码，但名字改了
        .name = "RGB-555",      
        .fourcc = V4L2_PIX_FMT_RGB555,
        .pixelformat = V4L2_PIX_FMT_RGB555,
        .bpp = 2,
        .colorspace = V4L2_COLORSPACE_SRGB,
        .regs = ov7670_fmt_rgb555,
        .cmatrix = { 179, -179, 0, -61, -176, 228 },
    },
    {
        .name = "YUV-422",
        .fourcc = V4L2_PIX_FMT_YUYV,
        .pixelformat = V4L2_PIX_FMT_YUYV,
        .bpp = 2,
        .colorspace = V4L2_COLORSPACE_JPEG,
        .regs = ov7670_fmt_yuv422,
        .cmatrix = { 128, -128, 0, -34, -94, 128 },
    },
    {
        .name = "RAWRGB8",
        .fourcc = V4L2_PIX_FMT_SBGGR8,
        .pixelformat = V4L2_PIX_FMT_SBGGR8,
        .bpp = 1,
        .colorspace = V4L2_COLORSPACE_SRGB,
        .regs = ov7670_fmt_raw,
        .cmatrix = { 0, 0, 0, 0, 0, 0 },
    }
};
#define N_OV7670_FMTS ARRAY_SIZE(formats)

/*
 * QCIF mode is done (by OV) in a very strange way - it actually looks like
 * VGA with weird scaling options - they do *not* use the canned QCIF mode
 * which is allegedly provided by the sensor.  So here's the weird register
 * settings.
 */
static struct reg_value ov7670_qcif_regs[] = {
	{ OV7670_REG_COM3, OV7670_COM3_SCALEEN | OV7670_COM3_DCWEN },
	{ OV7670_REG_COM3, OV7670_COM3_DCWEN },
	{ OV7670_REG_COM14, OV7670_COM14_DCWEN | 0x01},
	{ 0x73, 0xf1 },
	{ 0xa2, 0x52 },
	{ 0x7b, 0x1c },
	{ 0x7c, 0x28 },
	{ 0x7d, 0x3c },
	{ 0x7f, 0x69 },
	{ OV7670_REG_COM9, 0x38 },
	{ 0xa1, 0x0b },
	{ 0x74, 0x19 },
	{ 0x9a, 0x80 },
	{ 0x43, 0x14 },
	{ OV7670_REG_COM13, 0xc0 },
	{ 0xff, 0xff },
};

static struct ov7670_win_size ov7670_win_sizes[] = {
	/* VGA */
	{
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.com7_bit	= OV7670_COM7_FMT_VGA,
		.hstart		= 158,	/* These values from */
		.hstop		=  14,	/* Omnivision */
		.vstart		=  10,
		.vstop		= 490,
		.regs		= NULL,
	},
	/* CIF */
	{
		.width		= CIF_WIDTH,
		.height		= CIF_HEIGHT,
		.com7_bit	= OV7670_COM7_FMT_CIF,
		.hstart		= 170,	/* Empirically determined */
		.hstop		=  90,
		.vstart		=  14,
		.vstop		= 494,
		.regs		= NULL,
	},
	/* QVGA */
	{
		.width		= QVGA_WIDTH,
		.height		= QVGA_HEIGHT,
		.com7_bit	= OV7670_COM7_FMT_QVGA,
		.hstart		= 168,	/* Empirically determined */
		.hstop		=  24,
		.vstart		=  12,
		.vstop		= 492,
		.regs		= NULL,
	},
	/* QCIF */
	{
		.width		= QCIF_WIDTH,
		.height		= QCIF_HEIGHT,
		.com7_bit	= OV7670_COM7_FMT_VGA, /* see comment above */
		.hstart		= 456,	/* Empirically determined */
		.hstop		=  24,
		.vstart		=  14,
		.vstop		= 494,
		.regs		= ov7670_qcif_regs,
	}
};
#define N_WIN_SIZES ARRAY_SIZE(ov7670_win_sizes)

static int ov7670_i2c_read(struct ov7670_csi_dev *ov7670_csi,u8 reg,u8 *val)
{
    struct i2c_client *client = ov7670_csi->client;
    struct i2c_msg msg;
    int ret;
    u8 buf;
    
    /* 发送寄存器地址 */
    msg.addr = client->addr;
	msg.flags = 0;
    msg.len = 0;
	msg.buf = NULL;
    ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret < 0) {
		dev_err(&client->dev,"Error %d on register write\n",ret);
		return ret;
	}

    /* 特别注意，发送完从设备地址后要有个停止位 */
	msg.len = 1;
	msg.buf = &reg;
	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret < 0) {
		dev_err(&client->dev,"Error %d on register write\n",ret);
		return ret;
	}

	/* 读取返回值 */
	msg.flags = I2C_M_RD;
    msg.buf = &buf;
	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret >= 0) {
		*val = buf;
		ret = 0;
	}
	return ret;
}

static int ov7670_i2c_write(struct ov7670_csi_dev *ov7670_csi,u8 reg,u8 val)
{
    struct i2c_client *client = ov7670_csi->client;
    struct i2c_msg msg;
    int ret;
    u8 buf[2];

    buf[0] = reg;
    buf[1] = val;

    msg.addr  = client->addr;
    msg.flags = !I2C_M_RD;
    msg.buf   = NULL;
    msg.len   = 0;

    /* 特别注意，发送完从设备地址后要有个停止位 */
    ret = i2c_transfer(client->adapter,&msg,1);
    if (ret < 0) {
		dev_err(&client->dev,"Error %d on register write\n",ret);
		return ret;
	}

    msg.buf   = buf;
    msg.len   = 2;
    ret = i2c_transfer(client->adapter,&msg,1);
    if(ret != 1){
        dev_err(&client->dev,"failed when i2c write,errno is:%d\n",ret);
        return ret;
    }
    if((reg == OV7670_REG_COM7) && (val & OV7670_COM7_RESET))
        msleep(5);      //需要一点时间等待重启完成
    return 0;
}

/* 将不同的访问方式封装起来（比如如果需要的话，有i2c，sccb，smbus这些访问方式） */
static int ov7670_read_reg(struct ov7670_csi_dev *ov7670_csi,u8 reg,u8 *val)
{
    /* 现在只使用i2c */
    return ov7670_i2c_read(ov7670_csi,reg,val);
}

/* 将不同的访问方式封装起来（比如如果需要的话，有i2c，sccb，smbus这些访问方式） */
static int ov7670_write_reg(struct ov7670_csi_dev *ov7670_csi,u8 reg,u8 val)
{
    /* 现在只使用i2c */
    return ov7670_i2c_write(ov7670_csi,reg,val);
}

/* 将一个寄存器设置数组写入到ov7670中 */
static int ov7670_write_array(struct ov7670_csi_dev *ov7670_csi,struct reg_value *regs)
{
    int i = 1,ret;
    while(regs->addr != 0xff || regs->value != 0xff){
        ret = ov7670_write_reg(ov7670_csi,regs->addr,regs->value);
        if(ret){
            dev_err(ov7670_csi->dev,"occure error when write the %dTH reg ,errno is:%d\n",i++,ret);
            return ret;
        }
        regs++;  
        i++;  
    }
    return 0;
}

static int ov7670_init(struct ov7670_csi_dev *ov7670_csi)
{
	return ov7670_write_array(ov7670_csi, ov7670_default_regs);
}

static int ov7670_detect(struct ov7670_csi_dev *ov7670_csi)
{
	unsigned char v;
	int ret;

	ret = ov7670_init(ov7670_csi);
	if (ret < 0)
		return ret;
	ret = ov7670_read_reg(ov7670_csi, OV7670_REG_MIDH, &v);
	if (ret < 0)
		return ret;
	if (v != 0x7f) /* OV manuf. id. */
		return -ENODEV;
	ret = ov7670_read_reg(ov7670_csi, OV7670_REG_MIDL, &v);
	if (ret < 0)
		return ret;
	if (v != 0xa2)
		return -ENODEV;
	/*
	 * OK, we know we have an OmniVision chip...but which one?
	 */
	ret = ov7670_read_reg(ov7670_csi, OV7670_REG_PID, &v);
	if (ret < 0)
		return ret;
	if (v != 0x76)  /* PID + VER = 0x76 / 0x73 */
		return -ENODEV;
	ret = ov7670_read_reg(ov7670_csi, OV7670_REG_VER, &v);
	if (ret < 0)
		return ret;
	if (v != 0x73)  /* PID + VER = 0x76 / 0x73 */
		return -ENODEV;
	return 0;
}

static void ov7670_csi_deinterlaced_enable(struct ov7670_csi_dev *ov7670_csi,bool enable)
{
    u32 cr18 = readl(ov7670_csi->reg_base + CSI_CSICR18);

    if(enable){
        cr18 |= CSICR18_DEINTERLACE_EN;
    }else{
        cr18 &= ~CSICR18_DEINTERLACE_EN;
    }
    writel(cr18,ov7670_csi->reg_base + CSI_CSICR18);
}

static void ov7670_csi_buf_stride_set(struct ov7670_csi_dev *ov7670_csi,int stride)
{
    writel(stride,ov7670_csi->reg_base + CSI_CSIFBUF_PARA);
}

static void ov7670_csi_set_image_param(struct ov7670_csi_dev *ov7670_csi,int width,int height)
{
    int image_param = 0;
    u32 cr3 = readl(ov7670_csi->reg_base + CSI_CSICR3);

    image_param = (width << 16) | height;
    writel(image_param,ov7670_csi->reg_base + CSI_CSIIMAG_PARA);

    /* 刷新接收fifo的dma控制器 */
    writel(cr3 | CSICR3_DMA_REFLASH_RFF,ov7670_csi->reg_base + CSI_CSICR3);
}

static int ov7670_configure_csi(struct ov7670_csi_dev *ov7670_csi)
{
    struct v4l2_pix_format *pix = &ov7670_csi->pix;
    // u32 cr1;
    // u32 cr18;
    u32 width;

    if(pix->field == V4L2_FIELD_INTERLACED){
        ov7670_csi_deinterlaced_enable(ov7670_csi,true);
        ov7670_csi_buf_stride_set(ov7670_csi,pix->width);
        // ov7670_csi_deinterlaced_mode(ov7670_csi,ov7670_csi->std);
    }else{
        ov7670_csi_deinterlaced_enable(ov7670_csi,false);
        ov7670_csi_buf_stride_set(ov7670_csi,0);
    }

    switch(ov7670_csi->fmt->pixelformat){
        case V4L2_PIX_FMT_RGB565:
        case V4L2_PIX_FMT_RGB555:
            width = pix->width * 2;
            break;
        case V4L2_PIX_FMT_YUYV: 
            width = pix->width;
            break;
        default:
            pr_debug("unsupport pixformat!\n");
            return -EINVAL;
    }

    ov7670_csi_set_image_param(ov7670_csi,width,pix->height);

    /* mux_mipi? */

    return 0;
}

static void ov7670_csi_clk_enable(struct ov7670_csi_dev *ov7670_csi)
{
    clk_prepare_enable(ov7670_csi->clk_disp_axi);
    clk_prepare_enable(ov7670_csi->clk_disp_dcic);
    clk_prepare_enable(ov7670_csi->clk_csi_mclk);
}

static void ov7670_csi_clk_disable(struct ov7670_csi_dev *ov7670_csi)
{
    clk_disable_unprepare(ov7670_csi->clk_disp_axi);
    clk_disable_unprepare(ov7670_csi->clk_disp_dcic);
    clk_disable_unprepare(ov7670_csi->clk_csi_mclk);
}

/* 硬件复位csi interface */
static void ov7670_csihw_reset(struct ov7670_csi_dev *ov7670_csi)
{
    writel(readl(ov7670_csi->reg_base + CSI_CSICR3) | CSICR3_FRMCNT_RST ,ov7670_csi->reg_base + CSI_CSICR3);
    writel(CSICR1_RESET_VALUE,ov7670_csi->reg_base + CSI_CSICR1);
    writel(CSICR2_RESET_VALUE,ov7670_csi->reg_base + CSI_CSICR2);
    writel(CSICR3_RESET_VALUE,ov7670_csi->reg_base + CSI_CSICR3);
}

/* 初始化csi interface */
static  void ov7670_csi_init_interface(struct ov7670_csi_dev *ov7670_csi)
{
    u32 val = 0;
    u32 image_param;

    val = CSICR1_SOF_POL | CSICR1_REDGE | CSICR1_GCLK_MODE | CSICR1_HSYNC_POL | CSICR1_FCC;
    writel(val,ov7670_csi->reg_base + CSI_CSICR1);

    image_param = (800 << 16) | 640;    //为什么要在这里设一个立即值？？？？？
    writel(image_param,ov7670_csi->reg_base + CSI_CSIIMAG_PARA);

    val = CSICR3_DMA_REFLASH_RFF;
    writel(val,ov7670_csi->reg_base + CSI_CSICR3);
}

static void ov7670_csi_dmareq_rff_enable(struct ov7670_csi_dev *ov7670_csi)
{
    u32 cr2 = readl(ov7670_csi->reg_base + CSI_CSICR2);
    u32 cr3 = readl(ov7670_csi->reg_base + CSI_CSICR3);

    /* 用于rxfifo的dma传输的触发类型，设为INCR16 */
    cr2 |= 0xc0000000;

    cr3 |= CSICR3_DMA_REQ_EN_RFF;
    cr3 |= CSICR3_HRESP_ERR_EN;
    cr3 &= ~CSICR3_RXFF_LEVEL;
    cr3 |= 0x2 << 4;    //当数据量达到16开始启动传输

    writel(cr2,ov7670_csi->reg_base + CSI_CSICR2);
    writel(cr3,ov7670_csi->reg_base + CSI_CSICR3);
}

static void ov7670_csi_dmareq_rff_disable(struct ov7670_csi_dev *ov7670_csi)
{
    u32 cr3 = readl(ov7670_csi->reg_base + CSI_CSICR3);

    cr3 &= ~CSICR3_DMA_REQ_EN_RFF;
    cr3 &= ~CSICR3_HRESP_ERR_EN;

    writel(cr3,ov7670_csi->reg_base + CSI_CSICR3);
}

/* 开启中断 */
static void ov7670_csi_enable_int(struct ov7670_csi_dev *ov7670_csi,int arg)
{
    u32 cr1;
    cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);

    cr1 |= CSICR1_SOF_INTEN;
    cr1 |= CSICR1_SF_OR_INTEN;

    if(arg == 1){
        cr1 |= CSICR1_FB1_DMA_DONE_INTEN;
        cr1 |= CSICR1_FB2_DMA_DONE_INTEN;
    }
    
    writel(cr1,ov7670_csi->reg_base + CSI_CSICR1);
}

static void ov7670_csi_disable_int(struct ov7670_csi_dev *ov7670_csi)
{
    u32 cr1;
    cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);

    cr1 &= ~CSICR1_SOF_INTEN;
    cr1 &= ~CSICR1_SF_OR_INTEN;
    cr1 &= ~CSICR1_FB1_DMA_DONE_INTEN;
    cr1 &= ~CSICR1_FB2_DMA_DONE_INTEN;
    
    writel(cr1,ov7670_csi->reg_base + CSI_CSICR1);
}

static void ov7670_csi_simple_enable(struct ov7670_csi_dev *ov7670_csi,int arg)
{
    u32 cr18;
    cr18 = readl(ov7670_csi->reg_base + CSI_CSICR18);

    if(arg == 1){
        writel(cr18 | CSICR18_CSI_ENABLE,ov7670_csi->reg_base + CSI_CSICR18);
    }else{
        writel(cr18 & ~CSICR18_CSI_ENABLE,ov7670_csi->reg_base + CSI_CSICR18);
    }
}

static void ov7670_csi_init(struct ov7670_csi_dev *ov7670_csi)
{
    ov7670_csi_clk_enable(ov7670_csi);
    ov7670_csihw_reset(ov7670_csi);
    ov7670_csi_init_interface(ov7670_csi);
    ov7670_csi_dmareq_rff_disable(ov7670_csi); //这里为什么要disable？？？,应该在哪里开启呢
}

static void ov7670_csi_deinit(struct ov7670_csi_dev *ov7670_csi)
{
    ov7670_csihw_reset(ov7670_csi);
    ov7670_csi_init_interface(ov7670_csi);
    ov7670_csi_dmareq_rff_disable(ov7670_csi);
    ov7670_csi_clk_disable(ov7670_csi);
}

static void ov7670_csisw_reset(struct ov7670_csi_dev *ov7670_csi)
{
    u32 cr1,cr3,cr18,isr;
    
    /* disable csi */
    cr18 = readl(ov7670_csi->reg_base + CSI_CSICR18);
    cr18 &= ~(CSICR18_CSI_ENABLE);
    writel(cr18,ov7670_csi->reg_base + CSI_CSICR18);

    /* 清理rxfifo */
    cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);
    writel(cr1 & ~CSICR1_FCC,ov7670_csi->reg_base + CSI_CSICR1);
    cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);
    writel(cr1 | CSICR1_CLR_RXFIFO,ov7670_csi->reg_base + CSI_CSICR1); 

    /* 重启dma */
    cr3 = readl(ov7670_csi->reg_base + CSI_CSICR3);
    cr3 |= CSICR3_DMA_REFLASH_RFF | CSICR3_FRMCNT_RST;
    writel(cr3,ov7670_csi->reg_base + CSI_CSICR3);

    msleep(2);

    cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);
    writel(cr1 | CSICR1_FCC,ov7670_csi->reg_base + CSI_CSICR1);    

    isr = readl(ov7670_csi->reg_base + CSI_CSISR);
    writel(isr,ov7670_csi->reg_base + CSI_CSISR);

    /* 重新启动csi */
    cr18 |= (CSICR18_CSI_ENABLE);
    writel(cr18,ov7670_csi->reg_base + CSI_CSICR18);
}

static void ov7670_csi_tvdec_enable(struct ov7670_csi_dev *ov7670_csi, bool enable)
{
	unsigned long cr18 = readl(ov7670_csi->reg_base + CSI_CSICR18);
	unsigned long cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);

	if (enable == true) {
		cr18 |= (CSICR18_TVDECODER_IN_EN |
				CSICR18_BASEADDR_SWITCH_EN |
				CSICR18_BASEADDR_SWITCH_SEL |
				CSICR18_BASEADDR_CHG_ERR_EN);
		cr1 |= CSICR1_CCIR_MODE;
		cr1 &= ~(CSICR1_SOF_POL | CSICR1_REDGE);
	} else {
		cr18 &= ~(CSICR18_TVDECODER_IN_EN |
				CSICR18_BASEADDR_SWITCH_EN |
				CSICR18_BASEADDR_SWITCH_SEL |
				CSICR18_BASEADDR_CHG_ERR_EN);
		cr1 &= ~CSICR1_CCIR_MODE;
		cr1 |= CSICR1_SOF_POL | CSICR1_REDGE;
	}

	writel(cr18, ov7670_csi->reg_base + CSI_CSICR18);
	writel(cr1, ov7670_csi->reg_base + CSI_CSICR1);
}

static int ov7670_csi_enable(struct ov7670_csi_dev *ov7670_csi)
{
    struct v4l2_pix_format *pix = &ov7670_csi->pix;
    unsigned long flags;
    unsigned long val;
    int timeout,timeout2;
    
    ov7670_csisw_reset(ov7670_csi);
    
    if(pix->field == V4L2_FIELD_INTERLACED)
        ov7670_csi_tvdec_enable(ov7670_csi,true);
    
    local_irq_save(flags);
    for(timeout = 10000000 ; timeout > 0 ; timeout--){
        if(readl(ov7670_csi->reg_base + CSI_CSISR) & CSISR_SOF_INT){
            val = readl(ov7670_csi->reg_base + CSI_CSICR3);printk("line %d\n",__LINE__);
            writel(val | CSICR3_DMA_REFLASH_SFF,ov7670_csi->reg_base + CSI_CSICR3);
            /* 等待dma控制器重启完成 */
            for(timeout2 = 1000000 ; timeout2 > 0 ; timeout2--){
                /* 重启完成后该位会自动置为0 */
                if(readl(ov7670_csi->reg_base + CSI_CSICR3) & CSICR3_DMA_REFLASH_SFF)
                    cpu_relax();
                else
                    break;
            }printk("line %d\n",__LINE__);
            if(timeout2 <= 0){
                pr_err("reflash rxfifo dma controller tiemout!\n");
                local_irq_restore(flags);
                return -ETIME;
            }printk("line %d\n",__LINE__);
            /* For imx6sl csi, DMA FIFO will auto start when sensor ready to work,
			 * so DMA should enable right after FIFO reset, otherwise dma will lost data
			 * and image will split.
			 */
            ov7670_csi_dmareq_rff_enable(ov7670_csi);
            ov7670_csi_enable_int(ov7670_csi,1);
            ov7670_csi_simple_enable(ov7670_csi,1);
            break;
        }else{
            cpu_relax();
        }
    }
    if(timeout <= 0){
        pr_err("wait for SOF timeout!\n");
        local_irq_restore(flags);
        return -ETIME;
    }
    local_irq_restore(flags);
    return 0;
}

static void ov7670_csi_disable(struct ov7670_csi_dev *ov7670_csi)
{
    struct v4l2_pix_format *pix = &ov7670_csi->pix;

    ov7670_csi_dmareq_rff_disable(ov7670_csi);
    ov7670_csi_disable_int(ov7670_csi);

    writel(0,ov7670_csi->reg_base + CSI_CSIDMASA_FB1);
    writel(0,ov7670_csi->reg_base + CSI_CSIDMASA_FB2);

    ov7670_csi_buf_stride_set(ov7670_csi,0);

    if(pix->field == V4L2_FIELD_INTERLACED){
        ov7670_csi_deinterlaced_enable(ov7670_csi,false);
        ov7670_csi_tvdec_enable(ov7670_csi,false);
    }

    ov7670_csi_simple_enable(ov7670_csi,0);
}

static void ov7670_csi_update_csi_buf(struct ov7670_csi_dev *ov7670_csi,unsigned long phys,int bufnum)
{
    if(1 == bufnum)
        writel(phys,ov7670_csi->reg_base + CSI_CSIDMASA_FB2);
    else
        writel(phys,ov7670_csi->reg_base + CSI_CSIDMASA_FB1);
}

/* vb2 操作函数 */
static int ov7670_csi_videobuf_setup(struct vb2_queue *q, const struct v4l2_format *fmt,
unsigned int *num_buffers, unsigned int *num_planes,unsigned int sizes[], void *alloc_ctxs[])
{
    struct ov7670_csi_dev *ov7670_csi = vb2_get_drv_priv(q);

    alloc_ctxs[0] = ov7670_csi->alloc_ctx;
    sizes[0] = ov7670_csi->pix.sizeimage;

    if(0 == *num_buffers)
        *num_buffers = 16;
    if(!*num_planes && sizes[0] * *num_buffers > (MAX_VIDEO_MEM * 1024 * 1024))
        *num_buffers = (MAX_VIDEO_MEM * 1024 * 1024) / sizes[0];
    
    *num_planes = 1;

    return 0;
}

static int ov7670_csi_buf_prepare(struct vb2_buffer *vb)
{
    struct ov7670_csi_dev *ov7670_csi = vb2_get_drv_priv(vb->vb2_queue);
    // int ret;

    dev_dbg(ov7670_csi->dev,"%s (vb=0x%p) 0x%p %lu\n",__func__,vb,
            vb2_plane_vaddr(vb,0),vb2_get_plane_payload(vb,0));
    
    vb2_set_plane_payload(vb,0,ov7670_csi->pix.sizeimage);
    if(vb2_plane_vaddr(vb,0) && vb2_get_plane_payload(vb,0) > vb2_plane_size(vb,0))
        return -EINVAL;
    
    return 0;
}

static void ov7670_csi_buf_queue(struct vb2_buffer *vb)
{
    struct ov7670_csi_dev *ov7670_csi = vb2_get_drv_priv(vb->vb2_queue);
    struct ov7670_csi_buffer *buf = container_of(vb,struct ov7670_csi_buffer,vb);
    unsigned long flags;

    dev_dbg(ov7670_csi->dev,"%s (vb=0x%p) 0x%p %lu\n",__func__,vb,
            vb2_plane_vaddr(vb,0),vb2_get_plane_payload(vb,0));  
    
    spin_lock_irqsave(&ov7670_csi->slock,flags);
    list_add_tail(&buf->internal.queue,&ov7670_csi->capture);
    spin_unlock_irqrestore(&ov7670_csi->slock,flags);
}

static int ov7670_csi_start_streaming(struct vb2_queue *q, unsigned int count)
{
    struct ov7670_csi_dev *ov7670_csi = vb2_get_drv_priv(q);
    struct vb2_buffer *vb;
    struct ov7670_csi_buffer *buf;
    unsigned long phys;
    unsigned long flags;

    if(count < 2)   //至少需要两块缓存
        return -ENOBUFS;
    
    /*
	 * I didn't manage to properly enable/disable
	 * a per frame basis during running transfers,
	 * thus we allocate a buffer here and use it to
	 * discard frames when no buffer is available.
	 * Feel free to work on this ;)
	 */
    ov7670_csi->discard_size   = ov7670_csi->pix.sizeimage;
    ov7670_csi->discard_buffer = dma_alloc_coherent(ov7670_csi->v4l2_dev.dev,PAGE_ALIGN(ov7670_csi->discard_size),
    &ov7670_csi->discard_buffer_dma,GFP_DMA | GFP_KERNEL);
    if(!ov7670_csi->discard_buffer)
        return -ENOMEM;
    
    spin_lock_irqsave(&ov7670_csi->slock,flags);
    ov7670_csi->buf_discard[0].discard = true;
    list_add_tail(&ov7670_csi->buf_discard[0].queue,&ov7670_csi->discard);

    ov7670_csi->buf_discard[1].discard = true;
    list_add_tail(&ov7670_csi->buf_discard[1].queue,&ov7670_csi->discard);

    /* csi buf 0,imx6ull 只支持两个缓存寄存器 */
    buf = list_first_entry(&ov7670_csi->capture,struct ov7670_csi_buffer,internal.queue);
    buf->internal.buf_num = 0;
    vb = &buf->vb;
    vb->state = VB2_BUF_STATE_ACTIVE;

    phys = vb2_dma_contig_plane_dma_addr(vb,0);
    ov7670_csi_update_csi_buf(ov7670_csi,phys,buf->internal.buf_num);
    list_move_tail(ov7670_csi->capture.next,&ov7670_csi->active_bufs);

    /* csi buf 1 */
    buf = list_first_entry(&ov7670_csi->capture,struct ov7670_csi_buffer,internal.queue);
    buf->internal.buf_num = 1;
    vb = &buf->vb;
    vb->state = VB2_BUF_STATE_ACTIVE;

    phys = vb2_dma_contig_plane_dma_addr(vb,0);
    ov7670_csi_update_csi_buf(ov7670_csi,phys,buf->internal.buf_num);
    list_move_tail(ov7670_csi->capture.next,&ov7670_csi->active_bufs);

    spin_unlock_irqrestore(&ov7670_csi->slock,flags);

    return ov7670_csi_enable(ov7670_csi);
}

static void ov7670_csi_stop_streaming(struct vb2_queue *q)
{
    struct ov7670_csi_dev *ov7670_csi = vb2_get_drv_priv(q);
    struct ov7670_csi_buffer *buf,*tmp;
    unsigned long flags;
    void *p;

    ov7670_csi_disable(ov7670_csi);

    spin_lock_irqsave(&ov7670_csi->slock,flags);

    list_for_each_entry_safe(buf,tmp,&ov7670_csi->active_bufs,internal.queue){
        list_del_init(&buf->internal.queue);
        if(buf->vb.state == VB2_BUF_STATE_ACTIVE)
            vb2_buffer_done(&buf->vb,VB2_BUF_STATE_ERROR);
    }

    list_for_each_entry_safe(buf,tmp,&ov7670_csi->capture,internal.queue){
        list_del_init(&buf->internal.queue);
        if(buf->vb.state == VB2_BUF_STATE_ACTIVE)
            vb2_buffer_done(&buf->vb,VB2_BUF_STATE_ERROR);
    }

    INIT_LIST_HEAD(&ov7670_csi->capture);
    INIT_LIST_HEAD(&ov7670_csi->active_bufs);
    INIT_LIST_HEAD(&ov7670_csi->discard);

    p = ov7670_csi->discard_buffer;
    ov7670_csi->discard_buffer = NULL;

    spin_unlock_irqrestore(&ov7670_csi->slock,flags);

    dma_free_coherent(ov7670_csi->v4l2_dev.dev,ov7670_csi->discard_size,p,ov7670_csi->discard_buffer_dma);
}

static struct vb2_ops ov7670_csi_videobuf_ops = {
    .queue_setup = ov7670_csi_videobuf_setup,
    .buf_prepare = ov7670_csi_buf_prepare,
    .buf_queue   = ov7670_csi_buf_queue,
    .wait_prepare= vb2_ops_wait_prepare,
    .wait_finish = vb2_ops_wait_finish,
    .start_streaming = ov7670_csi_start_streaming,
    .stop_streaming  = ov7670_csi_stop_streaming,
};

static int ov7670_csi_open(struct file *filp)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(filp);
    struct vb2_queue *vb2_q = &ov7670_csi->vb2_q;
    int ret = 0;

    filp->private_data = ov7670_csi;

    if(mutex_lock_interruptible(&ov7670_csi->lock))
        return -ERESTARTSYS;
    
    ov7670_csi->alloc_ctx = vb2_dma_contig_init_ctx(ov7670_csi->dev);
    if(IS_ERR(ov7670_csi->alloc_ctx))
        goto unlock;

    vb2_q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vb2_q->io_modes = VB2_MMAP | VB2_USERPTR;
    vb2_q->drv_priv = ov7670_csi;
    vb2_q->ops = &ov7670_csi_videobuf_ops;
    vb2_q->mem_ops = &vb2_dma_contig_memops;
    vb2_q->buf_struct_size = sizeof(struct ov7670_csi_buffer);
    vb2_q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
    vb2_q->lock = &ov7670_csi->lock;

    ret = vb2_queue_init(vb2_q);
    if(ret < 0){
        mutex_unlock(&ov7670_csi->lock);
        goto eallocctx;
    }

    pm_runtime_get_sync(ov7670_csi->dev);

    request_bus_freq(BUS_FREQ_HIGH);

    ov7670_csi_init(ov7670_csi);

    mutex_unlock(&ov7670_csi->lock);

    return ret;
eallocctx:
    vb2_dma_contig_cleanup_ctx(ov7670_csi->alloc_ctx);
unlock:
    mutex_unlock(&ov7670_csi->lock);
    return ret;
}

static int ov7670_csi_close(struct file *filp)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(filp);
    struct vb2_queue *vb2_q = &ov7670_csi->vb2_q;

    mutex_lock(&ov7670_csi->lock);
    vb2_queue_release(vb2_q);
    ov7670_csi_deinit(ov7670_csi);
    mutex_unlock(&ov7670_csi->lock);

    filp->private_data = NULL;
    release_bus_freq(BUS_FREQ_HIGH);
    pm_runtime_put_sync_suspend(ov7670_csi->dev);
    return 0;
}

/* 摄像头利用读的方式获取数据 */
static ssize_t ov7670_csi_read(struct file *filep, char __user *buf, size_t size, loff_t *off)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(filep);
    int ret;

    mutex_lock(&ov7670_csi->lock);
    ret = vb2_read(&ov7670_csi->vb2_q,buf,size,off,filep->f_flags & O_NONBLOCK);
    mutex_unlock(&ov7670_csi->lock);

    return ret;
}

static int ov7670_csi_mmap(struct file *filp,struct vm_area_struct *vma)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(filp);
    int ret;

    if(mutex_lock_interruptible(&ov7670_csi->lock))
        return -ERESTARTSYS;
    ret = vb2_mmap(&ov7670_csi->vb2_q,vma);
    mutex_unlock(&ov7670_csi->lock);

    pr_debug("vma start=0x%08lx,size=%ld,ret=%d\n",(unsigned long)vma->vm_start,
             (unsigned long)vma->vm_end - (unsigned long)vma->vm_start,ret);
    return ret;
}

static struct v4l2_file_operations ov7670_csi_fops = {
    .owner          = THIS_MODULE,
    .open           = ov7670_csi_open,
    .release        = ov7670_csi_close,
    .unlocked_ioctl = video_ioctl2,
    .read           = ov7670_csi_read,
    .mmap           = ov7670_csi_mmap,
};

static int ov7670_csi_vidioc_querycap(struct file *file, void *fh, struct v4l2_capability *cap)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    printk(KERN_INFO"enter %s\n",__func__);
    WARN_ON(fh != file->private_data);

    strlcpy(cap->driver,OV7670_CSI_DRIVER_NAME,sizeof(cap->driver));
    strlcpy(cap->card,OV7670_CSI_DRIVER_DESCRIPTION,sizeof(cap->card));
    snprintf(cap->bus_info,sizeof(cap->bus_info),"i2c:%s",dev_name(ov7670_csi->dev));

    cap->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
    cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
    return 0;
}

/*
 * Store a set of start/stop values into the camera.
 */
static int ov7670_set_hw(struct ov7670_csi_dev *ov7670_csi, int hstart, int hstop,
		                 int vstart, int vstop)
{
	int ret;
	unsigned char v;
    /*
    * Horizontal: 11 bits, top 8 live in hstart and hstop.  Bottom 3 of
    * hstart are in href[2:0], bottom 3 of hstop in href[5:3].  There is
    * a mystery "edge offset" value in the top two bits of href.
    */
	ret =  ov7670_write_reg(ov7670_csi, OV7670_REG_HSTART, (hstart >> 3) & 0xff);
	ret += ov7670_write_reg(ov7670_csi, OV7670_REG_HSTOP, (hstop >> 3) & 0xff);
	ret += ov7670_read_reg(ov7670_csi, OV7670_REG_HREF, &v);
	v = (v & 0xc0) | ((hstop & 0x7) << 3) | (hstart & 0x7);
	msleep(10);
	ret += ov7670_write_reg(ov7670_csi, OV7670_REG_HREF, v);
    /*
    * Vertical: similar arrangement, but only 10 bits.
    */
	ret += ov7670_write_reg(ov7670_csi, OV7670_REG_VSTART, (vstart >> 2) & 0xff);
	ret += ov7670_write_reg(ov7670_csi, OV7670_REG_VSTOP, (vstop >> 2) & 0xff);
	ret += ov7670_read_reg(ov7670_csi, OV7670_REG_VREF, &v);
	v = (v & 0xf0) | ((vstop & 0x3) << 2) | (vstart & 0x3);
	msleep(10);
	ret += ov7670_write_reg(ov7670_csi, OV7670_REG_VREF, v);
	return ret;
}

static int ov7670_csi_vidioc_enum_fmt_vid_cap(struct file *file, void *fh, struct v4l2_fmtdesc *f)
{
    // struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    struct ov7670_csi_format *fmt;
    int index = f->index;
    printk(KERN_INFO"enter %s\n",__func__);
    WARN_ON(fh != file->private_data);

    fmt = &formats[index];
    strlcpy(f->description,fmt->name,sizeof(f->description));
    f->pixelformat = fmt->pixelformat;
    return 0;
}

static struct ov7670_csi_format *format_by_fourcc(int fourcc)
{
    int i;

    for(i = 0 ; i < NUM_FROMATS ; i++){
        if(formats[i].pixelformat == fourcc)
            return formats + i;
    }

    pr_err("unknown pixelformat:'%4.4s'\n",(char *)&fourcc);
    return NULL;
}

static int ov7670_csi_vidioc_try_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
    int ret = 0;
    int i,n_win_sizes = N_WIN_SIZES;
    unsigned char com7;
    struct ov7670_win_size *wsize;
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    struct ov7670_csi_format *fmt;
    struct v4l2_pix_format *pix = &f->fmt.pix;
 
    printk(KERN_INFO"enter %s\n",__func__);
    fmt = format_by_fourcc(pix->pixelformat);
    if(!fmt){
        dev_err(ov7670_csi->dev,"Fourcc format (0x%08x) invalid.\n",pix->pixelformat);
        return -EINVAL;
    }

    if(0 == pix->width || 0 == pix->height){
        dev_err(ov7670_csi->dev,"width %d,height %d is too small\n",pix->width,pix->height);
        return -EINVAL;
    }

    if(pix->field != V4L2_FIELD_INTERLACED)
        pix->field = V4L2_FIELD_NONE;
    
    /* 在支持的图像尺寸中，选择一个与请求的图像尺寸最接近的一个 */
    for(i = 0 , wsize = ov7670_win_sizes ; i < n_win_sizes ; i++ , wsize++){
        if(pix->width >= wsize->width && pix->height >= wsize->height){
            printk("pix->width:%d,pix->height:%d\n",pix->width,pix->height);
            printk("wsize->width:%d,wsize->height:%d\n",wsize->width,wsize->height);
            break;
        }
    }

    /* 如果没有找到符合条件的，则选择一个最小的 */
    if(i == n_win_sizes){
        wsize--; 
    }

    /* 光选择格式是不够的，还要相应的设置ov7670，也就是操作寄存器 */
    /*
	 * COM7 is a pain in the ass, it doesn't like to be read then
	 * quickly written afterward.  But we have everything we need
	 * to set it absolutely here, as long as the format-specific
	 * register sets list it first.
	 */
	com7 = fmt->regs[0].value;
	com7 |= wsize->com7_bit;
	ov7670_write_reg(ov7670_csi, OV7670_REG_COM7, com7);
	/*
	 * Now write the rest of the array.  Also store start/stops
	 */
	ov7670_write_array(ov7670_csi, fmt->regs + 1);
	ov7670_set_hw(ov7670_csi, wsize->hstart, wsize->hstop, wsize->vstart,wsize->vstop);
	
	if (wsize->regs)
		ret = ov7670_write_array(ov7670_csi, wsize->regs);

	/*
	 * If we're running RGB565, we must rewrite clkrc after setting
	 * the other parameters or the image looks poor.  If we're *not*
	 * doing RGB565, we must not rewrite clkrc or the image looks
	 * *really* poor.
	 *
	 * (Update) Now that we retain clkrc state, we should be able
	 * to write it unconditionally, and that will make the frame
	 * rate persistent too.
	 */
	if (ret == 0){
        // ret = ov7670_write(ov7670_csi, OV7670_REG_CLKRC, info->clkrc);
        ret = ov7670_write_reg(ov7670_csi, OV7670_REG_CLKRC, 0);
    }
		
    /* 将实际的图像尺寸记录下来 */
    pix->width = wsize->width;
    pix->height = wsize->height;
    pix->colorspace = fmt->colorspace;
    pix->bytesperline = fmt->bpp * pix->width;
    pix->sizeimage = pix->height * pix->bytesperline;

    return 0;
}   

static int ov7670_csi_vidioc_g_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    printk(KERN_INFO"enter %s\n",__func__);
    f->fmt.pix = ov7670_csi->pix;

    return 0;
}

static int ov7670_csi_vidioc_s_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    struct v4l2_pix_format *pix = &f->fmt.pix;
    int ret;
    printk(KERN_INFO"enter %s\n",__func__);
    ret = ov7670_csi_vidioc_try_fmt_vid_cap(file,ov7670_csi,f);
    if(ret < 0){
        return ret;
    }
    ov7670_csi->fmt = format_by_fourcc(pix->pixelformat);
    ov7670_csi->pix.width = pix->width;
    ov7670_csi->pix.height = pix->height;
    ov7670_csi->pix.bytesperline = pix->bytesperline;
    ov7670_csi->pix.sizeimage = pix->sizeimage;
    ov7670_csi->pix.field = pix->field;
    ov7670_csi->type = f->type;

    dev_dbg(ov7670_csi->dev,"set to pixelformat '%4.6s'\n",ov7670_csi->fmt->name);

    /* 实际配置csi硬件 */
    ov7670_configure_csi(ov7670_csi);
    return 0;
}

static int ov7670_csi_vidioc_reqbufs(struct file *file, void *fh, struct v4l2_requestbuffers *b)
{   
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    printk(KERN_INFO"enter %s\n",__func__);
    WARN_ON(fh != file->private_data);

    return vb2_reqbufs(&ov7670_csi->vb2_q,b);
}

static int ov7670_csi_vidioc_querybuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    int ret = 0;
    printk(KERN_INFO"enter %s\n",__func__);
    WARN_ON(fh != file->private_data);

    ret = vb2_querybuf(&ov7670_csi->vb2_q,b);

    if(!ret){
        /* 返回物理地址 */
        struct vb2_buffer *vb = ov7670_csi->vb2_q.bufs[b->index];
        if(b->flags & V4L2_BUF_FLAG_MAPPED)
            b->m.offset = vb2_dma_contig_plane_dma_addr(vb,0);
    }
    return ret;
}

static int ov7670_csi_vidioc_qbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    printk(KERN_INFO"enter %s\n",__func__);
    WARN_ON(fh != file->private_data);

    return vb2_qbuf(&ov7670_csi->vb2_q,b);
}

static int ov7670_csi_vidioc_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    printk(KERN_INFO"enter %s\n",__func__);
    WARN_ON(fh != file->private_data);

    return vb2_dqbuf(&ov7670_csi->vb2_q,b,file->f_flags & O_NONBLOCK);
}

static int ov7670_vidioc_streamon(struct file *file, void *fh, enum v4l2_buf_type i)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    printk(KERN_INFO"enter %s\n",__func__);
    WARN_ON(fh != file->private_data);

    if(i != V4L2_BUF_TYPE_VIDEO_CAPTURE)
        return -EINVAL;

    return vb2_streamon(&ov7670_csi->vb2_q,i);
}

static int ov7670_vidioc_streamoff(struct file *file, void *fh, enum v4l2_buf_type i)
{
    struct ov7670_csi_dev *ov7670_csi = video_drvdata(file);
    printk(KERN_INFO"enter %s\n",__func__);
    WARN_ON(fh != file->private_data);

    if(i != V4L2_BUF_TYPE_VIDEO_CAPTURE)
        return -EINVAL;

    return vb2_streamoff(&ov7670_csi->vb2_q,i);
}

static struct v4l2_ioctl_ops ov7670_csi_ioctl_ops = {
    /* 表示它是一个摄像头设备 */
    .vidioc_querycap = ov7670_csi_vidioc_querycap,

    /* 列举、获取、测试以及设置摄像头数据的格式 */
    .vidioc_enum_fmt_vid_cap = ov7670_csi_vidioc_enum_fmt_vid_cap,
    .vidioc_try_fmt_vid_cap  = ov7670_csi_vidioc_try_fmt_vid_cap,
    .vidioc_g_fmt_vid_cap    = ov7670_csi_vidioc_g_fmt_vid_cap,
    .vidioc_s_fmt_vid_cap    = ov7670_csi_vidioc_s_fmt_vid_cap,

    /* 缓存区操作 */
    .vidioc_reqbufs = ov7670_csi_vidioc_reqbufs,
    .vidioc_querybuf= ov7670_csi_vidioc_querybuf,
    .vidioc_qbuf    = ov7670_csi_vidioc_qbuf,
    .vidioc_dqbuf   = ov7670_csi_vidioc_dqbuf,

    /* 启动 / 停止 */
    .vidioc_streamoff = ov7670_vidioc_streamoff,
    .vidioc_streamon  = ov7670_vidioc_streamon,
};

static void ov7670_csi_release(struct video_device *vdev)
{

}

static void ov7670_csi_frame_done(struct ov7670_csi_dev *ov7670_csi,int bufnum,bool err)
{
    struct ov7670_csi_buffer *buf;
    struct ov7670_buf_internal *ibuf;
    struct vb2_buffer *vb;
    unsigned long phys;

    // void *virt;

    ibuf = list_first_entry(&ov7670_csi->active_bufs,struct ov7670_buf_internal,queue);

    if(ibuf->discard){
        /* 被丢弃的缓存不能返回到用户空间,只需将其加入到相应的链表中 */
        list_move_tail(ov7670_csi->active_bufs.next,&ov7670_csi->discard);
    }else{
        buf = container_of(ibuf,struct ov7670_csi_buffer,internal);
        vb = &buf->vb;
        phys = vb2_dma_contig_plane_dma_addr(vb,0);

        /* 给这块地址赋一点值，看效果 */
        // printk("vb2.length:%d\n",vb->v4l2_planes->length);
        // virt = dma_to_virt(NULL,phys);
        // memset(virt,0x99,vb->v4l2_planes->length / 2);
        // memset((u8 *)virt + vb->v4l2_planes->length / 2,0xf7,vb->v4l2_planes->length / 2);

        if(bufnum == 1){
            if(readl(ov7670_csi->reg_base + CSI_CSIDMASA_FB2) != phys){
                dev_err(ov7670_csi->dev,"fb addr error,%lx != %x\n",phys,readl(ov7670_csi->reg_base + CSI_CSIDMASA_FB2));
            }
        }else{
            if(readl(ov7670_csi->reg_base + CSI_CSIDMASA_FB1) != phys){
                dev_err(ov7670_csi->dev,"fb addr error,%lx != %x\n",phys,readl(ov7670_csi->reg_base + CSI_CSIDMASA_FB1));
            }
        }
        dev_dbg(ov7670_csi->dev, "%s (vb=0x%p) 0x%p %lu\n", __func__, vb,vb2_plane_vaddr(vb, 0),vb2_get_plane_payload(vb, 0));

        list_del_init(&buf->internal.queue);
        v4l2_get_timestamp(&vb->v4l2_buf.timestamp);
        vb->v4l2_buf.sequence = ov7670_csi->frame_count;
        if(err)
            vb2_buffer_done(vb,VB2_BUF_STATE_ERROR);
        else
            vb2_buffer_done(vb,VB2_BUF_STATE_DONE);
    }
    ov7670_csi->frame_count++;

    /* 将discard缓存配置到active缓存中 */
    /* 顿悟!!! 为什么要有一块缓存专门用于丢弃,当数据生成过快，capture链表中没有可用的缓存时,这时接收的数据无处存放,不就只能丢弃了 */
    if(list_empty(&ov7670_csi->capture)){
        if(list_empty(&ov7670_csi->discard)){
            return ;
        }
        ibuf = list_first_entry(&ov7670_csi->discard,struct ov7670_buf_internal,queue);
        ibuf->buf_num = bufnum;
        list_move_tail(ov7670_csi->discard.next,&ov7670_csi->active_bufs);
        ov7670_csi_update_csi_buf(ov7670_csi,ov7670_csi->discard_buffer_dma,bufnum);
    }

    buf = list_first_entry(&ov7670_csi->capture,struct ov7670_csi_buffer,internal.queue);
    buf->internal.buf_num = bufnum;
    list_move_tail(ov7670_csi->capture.next,&ov7670_csi->active_bufs);

    vb = &buf->vb;
    vb->state = VB2_BUF_STATE_ACTIVE;

    phys = vb2_dma_contig_plane_dma_addr(vb,0);
    ov7670_csi_update_csi_buf(ov7670_csi,phys,bufnum);
}

static irqreturn_t ov7670_csi_irq_handler(int irq,void *dev_id)
{
    struct ov7670_csi_dev *ov7670_csi = dev_id;
    unsigned long status;
    u32 cr1,cr3,cr18;

    spin_lock(&ov7670_csi->slock);

    status = readl(ov7670_csi->reg_base + CSI_CSISR);
    writel(status,ov7670_csi->reg_base + CSI_CSISR);

    if(list_empty(&ov7670_csi->active_bufs)){
        dev_warn(ov7670_csi->dev,"%s:active buffer is empty\n",__func__);

        spin_unlock(&ov7670_csi->slock);
        return IRQ_HANDLED;
    }

    /* 先打印警报信息 */
    if(status & CSISR_RFF_OR_INT)
        dev_warn(ov7670_csi->dev,"%s:rx fifo overflow !\n",__func__);
    if(status & CSISR_HRESP_ERR_INT)
        dev_warn(ov7670_csi->dev,"%s:detect hresponse error !\n",__func__);
    
    /* 对出错情况进行处理 */
    if(status & (CSISR_RFF_OR_INT & CSISR_HRESP_ERR_INT)){
        /* 软件复位 */
        /* disable csi */
        cr18 = readl(ov7670_csi->reg_base + CSI_CSICR18);
        cr18 &= ~(CSICR18_CSI_ENABLE);
        writel(cr18,ov7670_csi->reg_base + CSI_CSICR18);

        /* 清理rxfifo */
        cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);
        writel(cr1 & ~CSICR1_FCC,ov7670_csi->reg_base + CSI_CSICR1);
        cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);
        writel(cr1 & ~CSICR1_CLR_RXFIFO,ov7670_csi->reg_base + CSI_CSICR1); 
        cr1 = readl(ov7670_csi->reg_base + CSI_CSICR1);
        writel(cr1 | CSICR1_FCC,ov7670_csi->reg_base + CSI_CSICR1);

        /* 重启dma */
        cr3 = readl(ov7670_csi->reg_base + CSI_CSICR3);
        cr3 |= CSICR3_DMA_REFLASH_RFF;
        writel(cr3,ov7670_csi->reg_base + CSI_CSICR3);

        /* 重新启动csi */
        cr18 |= (CSICR18_CSI_ENABLE);
        writel(cr18,ov7670_csi->reg_base + CSI_CSICR18);
    }

    if(status & CSISR_ADDR_CH_ERR_INT){
          /* disable csi */
        cr18 = readl(ov7670_csi->reg_base + CSI_CSICR18);
        cr18 &= ~(CSICR18_CSI_ENABLE);
        writel(cr18,ov7670_csi->reg_base + CSI_CSICR18);

        /* 重启dma */
        cr3 = readl(ov7670_csi->reg_base + CSI_CSICR3);
        cr3 |= CSICR3_DMA_REFLASH_RFF;
        writel(cr3,ov7670_csi->reg_base + CSI_CSICR3);

        /* 重新启动csi */
        cr18 |= (CSICR18_CSI_ENABLE);
        writel(cr18,ov7670_csi->reg_base + CSI_CSICR18);
        pr_debug("base address switching change err!\n");
    }
    if((status & CSISR_DMA_TSF_DONE_FB1) && (status & CSISR_DMA_TSF_DONE_FB2)){
        /* 因为软件不能分辨这种情况,所以不处理这种情况 */
        pr_debug("skip two frames\n");
    }else if(status & CSISR_DMA_TSF_DONE_FB1){
        ov7670_csi_frame_done(ov7670_csi,0,false);
    }else if(status & CSISR_DMA_TSF_DONE_FB2){
        ov7670_csi_frame_done(ov7670_csi,1,false);
    }

    spin_unlock(&ov7670_csi->slock);

    return IRQ_HANDLED;
}

/* 从csi控制器设备树节点初始化其资源 */
static int parse_csi_dt(struct ov7670_csi_dev *ov7670_csi)
{
    struct device *dev = ov7670_csi->dev;
    struct device_node *csi_np;
    struct resource *res;
    u32 addr_base,addr_size;
    int ret = -1;

    dev_dbg(dev,"initialising csi interface\n");

    /* 获取csi控制器对应的节点 */
    csi_np = of_parse_phandle(dev->of_node,"csi-interface",0);
    if(!csi_np){
        dev_err(dev,"get csi interface device node failed\n");
        return -ENODEV;
    }

    ov7670_csi->irq = of_irq_get(csi_np,0);
    if(ov7670_csi->irq < 0){
        dev_err(dev,"get csi interface irq num failed\n");
        ret = ov7670_csi->irq;
        goto put_csi_np;
    }

    /* 映射寄存器地址 */
    // ov7670_csi->reg_base = of_iomap(csi_np,0);
    of_property_read_u32_index(csi_np,"reg",0,&addr_base);
    of_property_read_u32_index(csi_np,"reg",1,&addr_size);
    ov7670_csi->reg_addr_base = addr_base;
    ov7670_csi->reg_addr_size = addr_size;
    res = request_mem_region(addr_base,addr_size,"csi io memory");
    if(!res){
        dev_err(dev,"request csi io memory failed\n");
        ret = -ENOMEM;
        goto release_memreg;
    }
    
    ov7670_csi->reg_base = ioremap_nocache(res->start,res->end - res->start);
    if(IS_ERR(ov7670_csi->reg_base)){
        dev_err(dev,"failed to remap ioresource\n");
        ret = PTR_ERR(ov7670_csi->reg_base);
        goto release_memreg;
    }
    
    /* 获取时钟 */
    ov7670_csi->clk_csi_mclk = of_clk_get(csi_np,1);
    if(IS_ERR(ov7670_csi->clk_csi_mclk)){
        dev_err(dev,"could not get csi mclk clock\n");
        ret = PTR_ERR(ov7670_csi->clk_csi_mclk);
        goto resource_iounmap;
    }

    ov7670_csi->clk_disp_axi = of_clk_get(csi_np,0);
    if(IS_ERR(ov7670_csi->clk_disp_axi)){
        dev_err(dev,"could not get csi disp axi clock\n");
        ret = PTR_ERR(ov7670_csi->clk_disp_axi);
        goto put_csi_mclk;
    }

    ov7670_csi->clk_disp_dcic = of_clk_get(csi_np,2);
    if(IS_ERR(ov7670_csi->clk_disp_dcic)){
        dev_err(dev,"could not get csi disp dcic clock\n");
        ret = PTR_ERR(ov7670_csi->clk_disp_dcic);
        goto put_disp_axi;
    }

    /* 设置中断处理函数 */
    if(devm_request_irq(dev,ov7670_csi->irq,ov7670_csi_irq_handler,0,"csi",(void *)ov7670_csi)){
        dev_err(dev,"install csi irq handler failed!\n");
        ret = -ENODEV;
        goto put_disp_dcic;
    }

    of_node_put(csi_np);

    return 0;

put_disp_dcic:
    clk_put(ov7670_csi->clk_disp_dcic);
put_disp_axi:
    clk_put(ov7670_csi->clk_disp_axi);
put_csi_mclk:
    clk_put(ov7670_csi->clk_csi_mclk);
resource_iounmap:
    iounmap(ov7670_csi->reg_base);
release_memreg:
    release_mem_region(ov7670_csi->reg_addr_base,ov7670_csi->reg_addr_size);
put_csi_np:
    of_node_put(csi_np);
    return ret;
}

/* 释放由parse_csi_dt函数分配的资源 */
static void exit_csi_dt(struct ov7670_csi_dev *ov7670_csi)
{
    clk_put(ov7670_csi->clk_disp_dcic);
    clk_put(ov7670_csi->clk_disp_axi);
    clk_put(ov7670_csi->clk_csi_mclk);
    // free_irq(ov7670_csi->irq,(void *)ov7670_csi);
    iounmap(ov7670_csi->reg_base);
    release_mem_region(ov7670_csi->reg_addr_base,ov7670_csi->reg_addr_size);
}

static long ov7670_get_clk(struct ov7670_csi_dev *ov7670_csi)
{
    unsigned long ret;
    struct clk *osc_clk;
    struct device_node *clks_node;
    struct device *dev = ov7670_csi->dev;

    ov7670_csi->clk_csi_ov7670_sel = devm_clk_get(dev,"csi_ov7670_sel");
    if(IS_ERR(ov7670_csi->clk_csi_ov7670_sel)){
        dev_err(dev,"failed get clock csi_ov7670_sel!\n");
        ret = PTR_ERR(ov7670_csi->clk_csi_ov7670_sel);
        return ret;
    }

    ov7670_csi->clk_csi_ov7670_podf = devm_clk_get(dev,"csi_ov7670_podf");
    if(IS_ERR(ov7670_csi->clk_csi_ov7670_podf)){
        dev_err(dev,"failed get clock csi_ov7670_podf!\n");
        ret = PTR_ERR(ov7670_csi->clk_csi_ov7670_podf);
        return ret;
    }

    /* 时钟选择为 osc_clk */
    clks_node = of_find_node_by_name(NULL,"ccm");
    if(!clks_node){
        dev_err(dev,"find ccm device node failed!\n");
        return -1;
    }
    osc_clk = of_clk_get_by_name(clks_node,"osc");
    if(IS_ERR(osc_clk)){
        dev_err(dev,"failed get clock osc_clk!\n");
        ret = PTR_ERR(osc_clk);
        return ret;
    }

    clk_set_parent(ov7670_csi->clk_csi_ov7670_sel,osc_clk);
    clk_put(osc_clk);
    of_node_put(clks_node);
    /* 1分频 */
    clk_set_rate(ov7670_csi->clk_csi_ov7670_podf,0);
    return 0;
}

// static void test_func(struct ov7670_csi_dev *ov7670_csi)
// {
//     char buf[2] = {0};
//     ov7670_csi_init(ov7670_csi);
//     clk_prepare_enable(ov7670_csi->clk_csi_ov7670_sel);
//     clk_prepare_enable(ov7670_csi->clk_csi_ov7670_podf);
//     /* 先使能csi */
//     ov7670_csi_enable(ov7670_csi);
//     gpiod_set_value(ov7670_csi->reset_gpio,1);
//     gpiod_set_value(ov7670_csi->pwdn_gpio,0);
//     /* 读产品id */
//     ov7670_read_reg(ov7670_csi,OV7670_REG_MIDH,&buf[0]);
//     ov7670_read_reg(ov7670_csi,OV7670_REG_MIDL,&buf[1]);
//     printk("************* manuid:%x %x\n",buf[0],buf[1]);
// }

static int ov7670_csi_probe(struct i2c_client *ov7670_client,const struct i2c_device_id *id)
{   
    int ret = -ENOMEM;
    struct device *dev = &ov7670_client->dev;
    struct ov7670_csi_dev *ov7670_csi;
    struct v4l2_device *v4l2_dev;
    struct video_device *vdev;

    printk("line1 %d\n",__LINE__);
    printk("enter:%s\n",__func__);
    /* 分配私有数据结构 */
    ov7670_csi = devm_kzalloc(dev,sizeof(struct ov7670_csi_dev),GFP_KERNEL);
    if(!ov7670_csi){
        dev_err(dev,"allocate ov7670_csi_dev failed\n");
        return ret;
    }
    i2c_set_clientdata(ov7670_client,ov7670_csi);
    ov7670_csi->dev = &ov7670_client->dev;
    ov7670_csi->client = ov7670_client;
    printk("line1 %d\n",__LINE__);
    ret = parse_csi_dt(ov7670_csi);
    if(ret){
        dev_err(dev,"failed to parse csi resource!\n");
        return ret;
    }

    /* 获取提供给ov7670的时钟，该时钟由ccm直接提供而非由csi提供 */
    ret = ov7670_get_clk(ov7670_csi);
    if(ret){
        dev_err(dev,"failed to ov7670 mclk!\n");
        goto err_parse_csi_dt;
    }
    
    INIT_LIST_HEAD(&ov7670_csi->capture);
    INIT_LIST_HEAD(&ov7670_csi->active_bufs);
    INIT_LIST_HEAD(&ov7670_csi->discard);

    mutex_init(&ov7670_csi->lock);
    spin_lock_init(&ov7670_csi->slock);

    /* 注册v4l2_deivce */
    v4l2_dev = &ov7670_csi->v4l2_dev;
    snprintf(v4l2_dev->name,sizeof(v4l2_dev->name),"ov7670-csi");
    ret = v4l2_device_register(dev,v4l2_dev);
    if(ret < 0){
        dev_err(dev,"v4l2_device_register failed!,errno is:%d\n",ret);
        goto err_parse_csi_dt;
    }
    
    /* 注册video_device */
    vdev = video_device_alloc();
    if(!vdev){
        dev_err(dev,"allocate video device failed!\n");
        ret = -ENOMEM;
        goto err_vdev_alloc;
    }
    snprintf(vdev->name,sizeof(vdev->name),"ov7670-vdev");
    vdev->v4l2_dev = v4l2_dev;
    vdev->fops = &ov7670_csi_fops;
    vdev->ioctl_ops = &ov7670_csi_ioctl_ops;
    vdev->release = ov7670_csi_release;
    vdev->lock = &ov7670_csi->lock;
    
    vdev->queue = &ov7670_csi->vb2_q;
    ov7670_csi->vdev = vdev;
    video_set_drvdata(vdev,ov7670_csi);
    
    ret = video_register_device(vdev,VFL_TYPE_GRABBER,-1);
    if(ret < 0){
        dev_err(dev,"video_register_device failed!,error code is %d",ret);
        goto err_vdev_register;
    }

    ov7670_csi->client = ov7670_client;

    /* 获取复位和功耗选择的gpio */
    ov7670_csi->reset_gpio = devm_gpiod_get(&ov7670_client->dev,"reset");
    if(IS_ERR(ov7670_csi->reset_gpio)){
        dev_err(dev,"get reset gpio failed,error code is %ld",PTR_ERR(ov7670_csi->reset_gpio));
        goto err_vdev_register;
    }
    ov7670_csi->pwdn_gpio = devm_gpiod_get(&ov7670_client->dev,"pwdn");
    if(IS_ERR(ov7670_csi->pwdn_gpio)){
        dev_err(dev,"get pwdn gpio failed,error code is %ld",PTR_ERR(ov7670_csi->pwdn_gpio));
        goto err_vdev_register;
    }
    
    /* 设置DMA掩码 */
    ov7670_client->dev.coherent_dma_mask = DMA_BIT_MASK(32);

    /* 检查是否是o7670摄像头 */
    ret = ov7670_detect(ov7670_csi);
    if(ret){
        dev_dbg(&ov7670_client->dev,"chip found @ 0x%x (%s) is not an ov7670 chip.\n",
			     ov7670_client->addr << 1, ov7670_client->adapter->name);
		goto err_vdev_register;
    }

    // test_func(ov7670_csi);
    return 0;
err_vdev_register:
    video_device_release(vdev);
err_vdev_alloc:
    v4l2_device_unregister(v4l2_dev);
err_parse_csi_dt:
    free_irq(ov7670_csi->irq,(void *)ov7670_csi);
    exit_csi_dt(ov7670_csi);
    return ret;
}

static int ov7670_csi_remove(struct i2c_client *ov7670_client)
{
    struct ov7670_csi_dev *ov7670_csi;
    ov7670_csi = i2c_get_clientdata(ov7670_client);
    exit_csi_dt(ov7670_csi);
    video_unregister_device(ov7670_csi->vdev);
    v4l2_device_unregister(&ov7670_csi->v4l2_dev);
    return 0;
}

static const struct of_device_id ov7670_of_table[] = {
    {
        .compatible = "my,ov7670",
    },
    {},
};

static const struct i2c_device_id ov7670_id_table[] = {
    {"my,ov7670",0},
    {},
};

static struct i2c_driver ov7670_driver = {
    .driver = {
        .name = "ov7670",
        .owner = THIS_MODULE,
        .of_match_table = ov7670_of_table,
    },
    .probe    = ov7670_csi_probe,
    .remove   = ov7670_csi_remove,
    .id_table = ov7670_id_table,
};


static int __init ov7670_driver_init(void)
{   
    printk("enter:%s\n",__func__);
    i2c_add_driver(&ov7670_driver);
    return 0;
}

static void __exit ov7670_driver_exit(void)
{
    i2c_del_driver(&ov7670_driver);
}

module_init(ov7670_driver_init);
module_exit(ov7670_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("luo");



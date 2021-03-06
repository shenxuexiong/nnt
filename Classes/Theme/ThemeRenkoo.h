
# ifndef __NNT_THEME_RENKOO_3C1EFEF102774E178F46D87C70CFD36A_H_INCLUDED
# define __NNT_THEME_RENKOO_3C1EFEF102774E178F46D87C70CFD36A_H_INCLUDED

# import "NGLayerTheme.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgFill);

@interface ThemeRenkoo : NgLayerTheme <NgLayerTheme> {
    NgFill *img_indicator, *img_background;
}

@property (nonatomic, assign) CGColorRef borderColor;

//! init with color pattele.
- (id)initWith:(byte const*[2])data len:(usize const [2])len;

@end

@interface ThemeRenkooGreen : ThemeRenkoo

@end

NNT_END_HEADER_OBJC

# endif
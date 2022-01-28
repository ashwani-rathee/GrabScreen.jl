module GrabScreen

using CxxWrap
@wrapmodule("./src/libgrabscreen.so")

using Colors, ColorVectorSpace
using FixedPointNumbers

export screenshot_gray
export screenshot_rgb  
export screenshot_bgra

function __init__()
  @initcxx
end

"""
    screenshot_gray(Width= 1920, Height= 1080; originx= 0, originy= 0)
"""
function screenshot_gray(Width= 1920, Height= 1080; originx= 0, originy= 0)
    res = GrabScreen.screenshot(Width, Height, originx, originy, 2);
    res = reinterpret(Gray{N0f8}, res)
    res = reshape(res, Width, Height)
    res =  res'
end

"""
    screenshot_bgra(Width= 1920, Height= 1080; originx= 0, originy= 0)
This is much faster than other methods
"""
function screenshot_bgra(Width= 1920, Height= 1080; originx= 0, originy= 0)
    res = GrabScreen.screenshot(Width, Height,  originx, originy, 0);
    res = reinterpret(BGRA{N0f8}, res)
    res = reshape(res , Width, Height)
    res =  res'
end

"""
    screenshot_rgb(Width= 1920, Height= 1080; originx= 0, originy= 0)   

"""
function screenshot_rgb(Width= 1920, Height= 1080; originx= 0, originy= 0)
    res = GrabScreen.screenshot(Width, Height, originx, originy, 1); # 14ms
    res = reinterpret(RGB{N0f8}, res) #144ns
    res = reshape(res , Width, Height) #24ns
    res = res'
end

end # module

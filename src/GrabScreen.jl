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
    res = GrabScreen.screenshot(Width, Height, originx, originy);
    res = reinterpret(BGRA{N0f8}, res)
    res = Gray.(reshape(res , Width, Height))
    res =  res'
end

"""
    screenshot_bgra(Width= 1920, Height= 1080; originx= 0, originy= 0)
This is much faster than other methods
"""
function screenshot_bgra(Width= 1920, Height= 1080; originx= 0, originy= 0)
    res = GrabScreen.screenshot(Width, Height,  originx, originy);
    res = reinterpret(BGRA{N0f8}, res)
    res = reshape(res , Width, Height)
    res =  res'
end

"""
    screenshot_rgb(Width= 1920, Height= 1080; originx= 0, originy= 0)   

"""
function screenshot_rgb(Width= 1920, Height= 1080; originx= 0, originy= 0)
    res = GrabScreen.screenshot(Width, Height, originx, originy);
    res = reinterpret(BGRA{N0f8}, res)
    res = RGB.(reshape(res , Width, Height))
    res =  res'
end

end # module

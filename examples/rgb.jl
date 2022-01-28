using Images
using GLMakie
using GrabScreen

println("Step 2: Set original image shower")
img = screenshot_gray(800,600)
fig = Figure(size = (800,600), title = "Object Tracker")
ax = GLMakie.Axis(
    fig[1, 1],
    aspect = DataAspect(),
    xlabel = "x",
    xlabelcolor = :black,
    ylabel = "y label",
    ylabelcolor = :white,
    title = "Input Image",
    backgroundcolor = :black,
    labelcolor = :white,
)

hidedecorations!(ax)
node = Observable(rotr90(img))
makieimg = image!(ax, node)

display(fig)
while true
    img = screenshot_rgb(800,600)
    node[] = rotr90(img)
    sleep(1 / 30)
end
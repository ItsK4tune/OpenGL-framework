#include "window.h"
#include <iostream>
#include "resource_manager.h"
#include "global.h"
#include "camera.h"

Window::Window(int major, int minor, const std::string &title)
    : m_window(nullptr), m_title(title), m_major(major), m_minor(minor)
{
    if (!glfwInit())
    {
        throw std::runtime_error("[Window::Window] Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(Global::ScreenWidth, Global::ScreenHeight, m_title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("[Window::Window] Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("[Window::Window] Failed to initialize GLAD");
    }

    glViewport(0, 0, Global::ScreenWidth, Global::ScreenHeight);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

std::unique_ptr<Window> Window::Create(int major, int minor, const std::string &title)
{
    return std::unique_ptr<Window>(new Window(major, minor, title));
}

void Window::SetCallback()
{
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow *window, int width, int height)
                                   { glViewport(0, 0, width, height); });
}

void Window::Initialize()
{
    ResourceManager::Instance().LoadFromFile("script/load/test.txt");
}

void Window::MainLoop()
{
    auto camera = std::make_shared<Camera>(45.0f, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ResourceManager::Instance().Draw(camera->GetViewMatrix(), camera->GetPerspectiveMatrix());

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

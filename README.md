# Atlas - A C++ MVC Web Framework

Atlas is a modern, lightweight MVC (Model-View-Controller) web framework built in C++. It is designed to provide high performance and flexibility for web developers who prefer the power and control of C++.

## Features

- **HTTP Request and Response Handling**: Built-in classes for managing cookies, requests, and responses.
- **Routing**: Simplify routing and map HTTP methods (GET, POST, etc.) to specific controllers.
- **Middleware Support**: Add custom middleware for tasks like authentication, logging, or request validation.
- **Lightweight and Fast**: Designed for minimal overhead and high performance.
- **Modular Design**: Easily extendable and customizable to fit your project needs.

## Getting Started

### Prerequisites

- A C++17 (or later) compatible compiler
- CMake (3.10 or higher)
- Basic knowledge of C++ and web development concepts

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/tamuka27/atlas.git
   cd atlas
   ```

2. Build the framework:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. Run the sample application:
   ```bash
   ./atlas_sample
   ```

## Usage

### Creating a New Atlas Application

1. Initialize a new project:
   ```bash
   ./atlas init my_project
   cd my_project
   ```

2. Define your routes in `routes.cpp`:
   ```cpp
   #include "atlas/router.h"

   void setupRoutes(atlas::Router& router) {
       router.get("/", [](const atlas::Request& req, atlas::Response& res) {
           res.setBody("Welcome to Atlas!");
       });

       router.post("/submit", [](const atlas::Request& req, atlas::Response& res) {
           res.setBody("Form submitted successfully!");
       });
   }
   ```

3. Build and run your application:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ./my_project
   ```

4. Open your browser and visit `http://localhost:8080` to see your app in action.

### Directory Structure

```plaintext
my_project/
├── src/
│   ├── controllers/   # Controller files
│   ├── models/        # Model files
│   ├── views/         # HTML templates and static files
│   └── routes.cpp     # Application routes
├── CMakeLists.txt
└── main.cpp           # Application entry point
```

### Example

#### Controller Example

```cpp
#include "atlas/controller.h"

class UserController : public atlas::Controller {
public:
    void getUser(const atlas::Request& req, atlas::Response& res) {
        res.setBody("User details: ID = " + req.getParam("id"));
    }
};
```

#### Adding Routes

```cpp
void setupRoutes(atlas::Router& router) {
    UserController userController;
    
    router.get("/user/:id", [&](const atlas::Request& req, atlas::Response& res) {
        userController.getUser(req, res);
    });
}
```

## Contributing

Contributions are welcome! If you have ideas, bug reports, or feature requests, feel free to open an issue or submit a pull request.

### Development Setup

1. Fork the repository and clone it locally.
2. Create a feature branch for your changes.
3. Commit your work with clear messages.
4. Open a pull request for review.

## License

Atlas is licensed under the [MIT License](LICENSE).

---

Feel free to reach out if you have questions or suggestions. Let’s build something amazing with Atlas!

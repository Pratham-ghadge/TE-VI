var app = angular.module('authApp', []);

app.controller('AuthController', function ($scope) {
    // 1. DATA (The Model)
    $scope.isRegisterMode = false;
    $scope.regData = {};
    $scope.loginData = {};

    // 2. LOGIC (The Controller)
    $scope.toggleMode = function () {
        $scope.isRegisterMode = !$scope.isRegisterMode;
    };

    $scope.handleRegister = function (isValid) {
        if (isValid) {
            alert("Success! " + $scope.regData.firstName + " is now registered.");
            console.log("Registered User Data:", $scope.regData);
            $scope.toggleMode();
        } else {
            alert("Please fill all fields correctly!");
        }
    };

    $scope.handleLogin = function () {
        // Two-way binding allows us to access $scope.loginData instantly
        if ($scope.loginData.username === "admin" && $scope.loginData.password === "123") {
            alert("Welcome Back, Admin!");
        } else {
            alert("Login Failed. Try Username: admin, Pass: 123");
        }
    };
});
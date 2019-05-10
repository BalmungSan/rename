#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "functions.h"

// Maximum acceptable error when comparing double values.
#define TOLERANCE 0.00005d

// Terminal color constants.
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESETCOLOR "\033[0m"

// Global var to keep track of the number of failed tests.
unsigned int number_failed;

/**
 * Asserts that two double values are equals, within the allowed tolerance.
 * Prints to console if the test passed or not.
 */
void assert(const double result, const double expected, const char* test_description) {
  if (fabs(result - expected) > TOLERANCE) {
    ++number_failed;
    printf(RED "Test: '%s' FAILED!\n\t%f did not equal %f\n" RESETCOLOR, test_description, expected, result);
  } else {
    printf(GREEN "Test: '%s' PASSED!\n" RESETCOLOR, test_description);
  }
}

/**
 * Asserts that two double values are equals, within the allowed tolerance.
 * Prints to console if the test passed or not, together with the iteration number.
 */
void for_assert(const double result, const double expected, const char* test_description, const int i) {
  if (fabs(result - expected) > TOLERANCE) {
    ++number_failed;
    printf(RED "Test: '%s' (%i) FAILED!\n\t%f did not equal %f\n" RESETCOLOR, test_description, i, expected, result);
  } else {
    printf(GREEN "Test: '%s' (%i) PASSED!\n" RESETCOLOR, test_description, i);
  }
}

/**
 * Checks that the size_triangular_matrix return correct results.
 */
void test_size_triangular_matrix() {
  size_t n = 5;
  size_t expected = 10;

  size_t result = size_triangular_matrix(n);

  assert(result, expected, "test_size_triangular_matrix");
}

/**
 * Checks that the compute_acceleration function works for arrays of one element.
 */
void test_compute_acceleration_one_element() {
  #define size 1
  Vector forces[size] = { { 30, 30 } };
  ParticleProperties particle_properties[size] = { { 3 } };
  Vector accelerations[size] = { { 0 } };

  compute_acceleration(size, particle_properties, forces, accelerations);

  assert(accelerations[0].x_component, 10.0d, "test_compute_acceleration_one_element - x_component");
  assert(accelerations[0].y_component, 10.0d, "test_compute_acceleration_one_element - y_component");
  #undef size
}

/**
 * Checks that the compute_acceleration function works for arrays of multiple elements.
 */
void test_compute_acceleration_multiple_elements() {
  #define size 3
  Vector forces[size] = { { -12.58, -15.896 }, { 13.945, -200.826 }, { -543.62, -0.62 } };
  ParticleProperties particle_properties[size] = { { 0.367 }, { 3.967 }, { 0.52 } };
  Vector accelerations[size] = { { 0 } };

  compute_acceleration(size, particle_properties, forces, accelerations);

  Vector expected[size] = { { -34.2779d, -43.31335149863761d }, { 3.5152508192588856d, -50.6241d }, { -1045.4231d, -1.1923d } };
  for (size_t i = 0; i < size; ++i) {
    for_assert(accelerations[i].x_component, expected[i].x_component, "test_compute_acceleration_multiple_elements - x_component", i);
    for_assert(accelerations[i].y_component, expected[i].y_component, "test_compute_acceleration_multiple_elements - y_component", i);
  }
  #undef size
}

/**
 * Checks that the compute_velocity function works for arrays of one element.
 */
//void test_compute_velocity_one_element() {
//  #define size 1
//  Vector acceleration[size] = { { 42.53, -631.431 } };
//  double dt = 0.00025;
//  Vector velocities[size] = { { 0, 0 } };
//  Vector resultant_velocity[size] = { { 0 } };
//
//  compute_velocity(size, acceleration, dt, velocities, resultant_velocity);
//
//  assert(resultant_velocity[0].x_component, 0.010632500000000001d, "test_compute_velocity_one_element - x_component");
//  assert(resultant_velocity[0].y_component, -0.15785775000000002d, "test_compute_velocity_one_element - y_component");
//  #undef size
//}

/**
 * Checks that the compute_velocity function works for arrays of multiple elements.
 */
//void test_compute_velocity_multiple_elements() {
//  #define size 3
//  Vector acceleration[size] = { { -10.59, 162.35 }, { , }, { , } };
//  double dt = 0.00025;
//  Vector velocities[size] = { { 5, 2 }, { , }, { , } };
//  Vector resultant_velocity[size] = { { 0 } };
//
//  compute_velocity(size, acceleration, dt, velocities, resultant_velocity);
//
//  Vector expected[size] = { { -34.2779d, -43.31335149863761d }, { 3.5152508192588856d, -50.6241d }, { -1045.4231d, -1.1923d } };
//  for (size_t i = 0; i < size; ++i) {
//    for_assert(resultant_velocity[i].x_component, expected[i].x_component, "test_compute_velocity_multiple_elements - x_component", i);
//    for_assert(resultant_velocity[i].y_component, expected[i].y_component, "test_compute_velocity_multiple_elements - y_component", i);
//  }
//  #undef size
//}

/**
 * Checks that the displace_particles function works for arrays of one element.
 */
void test_displace_particles_one_element() {
  #define size 1
  Vector displacements[size] = { { 50, -50 } };
  Particle particles[size] = { { 0, 100, 0 } };

  displace_particles(size, displacements, particles);

  assert(particles[0].x_coordinate, 50.0d, "test_displace_particles_one_element - x_coordinate");
  assert(particles[0].y_coordinate, 50.0d, "test_displace_particles_one_element - y_coordinate");
  #undef size
}

/**
 * Checks that the displace_particles function works for arrays of multiple elements.
 */
void test_displace_particles_multiple_elements() {
  #define size 3
  Vector displacements[size] = { { 0, 0 }, { 0.000015, -0.000033 }, { -15, 30 } };
  Particle particles[size] = { { 0, 100, 0 }, { 0.11111, 2.100000, 0 }, { 15, -30, 0 } };

  displace_particles(size, displacements, particles);

  Particle expected[size] = { { 0.0d, 100.0d, 0 }, { 0.111125, 2.0999967, 0 }, { 0.0d, 0.0d, 0 } };
  for (size_t i = 0; i < size; ++i) {
    for_assert(particles[i].x_coordinate, expected[i].x_coordinate, "test_displace_particles_multiple_elements - x_coordinate", i);
    for_assert(particles[i].y_coordinate, expected[i].y_coordinate, "test_displace_particles_multiple_elements - y_coordinate", i);
  }
  #undef size
}

/**
 * Tests entry point.
 * All tests run here.
 */
int main(void) {
  // Initialize the number of failed tests.
  number_failed = 0;

  // Execute all tests.
  test_size_triangular_matrix();
  test_compute_acceleration_one_element();
  test_compute_acceleration_multiple_elements();
  //test_compute_velocity_one_element();
  //test_compute_velocity_multiple_elements();
  test_displace_particles_one_element();
  test_displace_particles_multiple_elements();

  // If, at least one test failed, exit with an error code.
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
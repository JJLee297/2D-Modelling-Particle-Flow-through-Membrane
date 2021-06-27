class Particle {
  public:
    Particle(int xpos, int ypos);
    void moveParticle();
  private:
    int x;
    int y;
    bool stuck;
}

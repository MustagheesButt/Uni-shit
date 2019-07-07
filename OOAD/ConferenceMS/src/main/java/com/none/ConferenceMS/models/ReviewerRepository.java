package com.none.ConferenceMS.models;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ReviewerRepository extends JpaRepository<Reviewer, Integer> {

    public List<Reviewer> findByEmail(String email);
    
}
package com.none.ConferenceMS.models;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface PaperRepository extends JpaRepository<Paper, Integer> {

    public List<Paper> findBySubmittedBy(int submittedBy);
    
}